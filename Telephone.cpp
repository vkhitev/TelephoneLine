#include "Telephone.h"
#include "TelephoneLine.h"
#include "SwitchingCenter.h"
#include "Utility.h"

#include "TelephoneCallingPanelState.h"
#include "TelephoneContactListState.h"
#include "TelephoneCallHistoryState.h"
#include "TelephoneGetCallState.h"
#include "TelephoneContactState.h"
#include "TelephoneAddContactState.h"

#include <iostream>
#include <thread>

Telephone::Telephone(AppContext context, const std::string& nativeNumber, TelephoneLine& line)
	: mTelephoneLine(line)
	, mSwitchingCenter(line.getSwitchingCenter())
	, mDataBase()
	, mNativeNumber(nativeNumber)
	, mDialedNumber()
	, mIsCalling(false)
	, mIsConnected(false)
	, mIsGettingCall(false)
	, mTimer()
	, mCaller()
	, mStateStack(context)
	, mPosition()
	, mSize()
	, mStateParam()
{
	std::cout << "Telephone created, number: " << nativeNumber << std::endl;
	registerStates();
	mStateStack.pushState(States::CallingPanel);
}

void Telephone::setDialedNumber(const std::string& number)
{
	mDialedNumber = number;
}

const std::string& Telephone::getDialedNumber() const
{
	return mDialedNumber;
}

void Telephone::setNativeNumber(const std::string& number)
{
	mNativeNumber = number;
}

const std::string& Telephone::getNativeNumber() const
{
	return mNativeNumber;
}

void Telephone::addContact(const std::string& firstName, const std::string& lastName, const std::string& number)
{
	mDataBase.addContact(Contact(firstName, lastName, number));
}

void Telephone::addContact(const Contact& contact)
{
	mDataBase.addContact(contact);
}

void Telephone::removeContact(const std::string& firstName, const std::string& lastName)
{
	mDataBase.removeContact(firstName, lastName);
}

void Telephone::removeContact(const Contact& contact)
{
	mDataBase.removeContact(contact);
}

void Telephone::sendMessage(const std::string& number, const std::string& text)
{
	if (auto center = mSwitchingCenter.lock())
	{
		if (center->sendMessage(*this, number, text))
		{
			mDataBase.registerMessage(Message::State::Outgoing, number, getCurrentTime(), text);
			std::cout << "Message has been sent" << std::endl;
		}
	}
	else
	{
		std::cout << "This telephone is not connected to switching center" << std::endl;
	}
}

void Telephone::call()
{
	if (isBusy())
	{
		std::cout << "Your telephone is busy" << std::endl;
		return;
	}
	if (isGettingCall())
	{
		std::cout << "You must accept or decline incoming call" << std::endl;
		return;
	}
	if (auto center = mSwitchingCenter.lock())
	{
		setCalling(true);
		center->connect(*this, mDialedNumber);
	}
	else
	{
		std::cout << "This telephone is not connected to switching center" << std::endl;
	}
}

const TelephoneDB& Telephone::getDataBase() const
{
	return mDataBase;
}

void Telephone::accept()
{
	if (mIsGettingCall)
	{
		mTimer.reset();
		mIsConnected = true;
		mIsGettingCall = false;
	}
}

void Telephone::decline()
{
	if (mIsGettingCall)
	{
		auto duration = static_cast<unsigned int>(mTimer.elapsedS().count());
		mDataBase.registerCall(RegisteredCall::State::Missed, mCaller, getCurrentTime(), 0);
		mIsGettingCall = false;
	}
}

void Telephone::connect()
{
	if (!mIsConnected)
	{
		mTimer.reset();
		mIsConnected = true;
		mIsCalling = false;
	}
}

void Telephone::disconnect()
{
	auto duration = static_cast<unsigned int>(mTimer.elapsedS().count());

	// Отключение до начала разговора
	if (mIsCalling)
	{
		mIsCalling = false;
		mDataBase.registerCall(RegisteredCall::State::Outgoing, mDialedNumber, getCurrentTime(), 0);
	}
	// Отключение во время разговора
	else if (mIsConnected)
	{
		mIsConnected = false;
		// Если звонок исходящий
		if (mCaller.empty())
		{
			mDataBase.registerCall(RegisteredCall::State::Outgoing, mDialedNumber, getCurrentTime(), duration);
		}
		// Звонок входящий
		else
		{
			mDataBase.registerCall(RegisteredCall::State::Imcoming, mCaller, getCurrentTime(), duration);
			mCaller.clear();
		}
	}
}

bool Telephone::isConnected() const
{
	return mIsConnected;
}

bool Telephone::isBusy() const
{
	return mIsConnected || mIsCalling;
}

void Telephone::getCall(const std::string& caller)
{
	mIsGettingCall = true;
	mCaller = caller;
}

void Telephone::getMessage(const std::string& sender, const std::string& text)
{
	mDataBase.registerMessage(Message::State::Imcoming, sender, getCurrentTime(), text);
}

std::string Telephone::getCaller() const
{
	return mDataBase.findName(mCaller);
}

bool Telephone::isGettingCall() const
{
	return mIsGettingCall;
}

void Telephone::setCalling(bool flag)
{
	mIsCalling = flag;
}

bool Telephone::isCalling() const
{
	return mIsCalling;
}

bool Telephone::isInConnectionZone() const
{
	return !mSwitchingCenter.expired();
}

void Telephone::setSwicthingCenter(const std::shared_ptr<SwitchingCenter>& center)
{
	disconnect();
	if (!center)
	{
		mSwitchingCenter.reset();
		return;
	}
	
	mSwitchingCenter = center;
	auto calls = center->getLateCalls(mNativeNumber);
	auto messages = center->getLateMessages(mNativeNumber);

	for (const auto& call : calls)
	{
		mDataBase.registerCallWithNumber(call);
	}
	for (const auto& message : messages)
	{
		mDataBase.registerMessageWithNumber(message);
	}
}

void Telephone::connectToNearestSwitchingCenter()
{
	setSwicthingCenter(mTelephoneLine.getSwitchingCenter());
}

void Telephone::handleEvent(const sf::Event& event)
{
	mStateStack.handleEvent(event);
}

void Telephone::update(sf::Time dt)
{
	mStateStack.update(dt);
}

void Telephone::draw() const
{
	mStateStack.draw();
}

void Telephone::registerStates()
{
	mStateStack.registerState<TelephoneCallingPanelState>(States::CallingPanel, *this);
	mStateStack.registerState<TelephoneContactListState>(States::ContactList, *this);
	mStateStack.registerState<TelephoneCallHistoryState>(States::CallHistory, *this); 
	mStateStack.registerState<TelephoneContactState>(States::Contact, *this);
	mStateStack.registerState<TelephoneGetCallState>(States::GetCall, *this);
	mStateStack.registerState<TelephoneAddContactState>(States::AddContact, *this);
}

void Telephone::setPosition(const sf::Vector2f& position)
{
	mPosition = position;
}

void Telephone::setSize(const sf::Vector2f& size)
{
	mSize = size;
}

sf::Vector2f Telephone::getPosition() const
{
	return mPosition;
}

sf::Vector2f Telephone::getSize() const
{
	return mSize;
}

void Telephone::setStateParam(const std::string& param)
{
	mStateParam = param;
}

std::string Telephone::getStateParam() const
{
	return mStateParam;
}