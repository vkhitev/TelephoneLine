#include "SwitchingCenter.h"
#include "Utility.h"

#include <thread>
#include <iostream>
#include <regex>

const int SwitchingCenter::sMaxNumberDigits = 12;

SwitchingCenter::SwitchingCenter(AppContext context)
	: mRegisteredTelephones()
	, mLateCalls()
	, mLateMessages()
{
	std::cout << "Switching center created" << std::endl;
}

void SwitchingCenter::registerTelephone(const std::shared_ptr<Telephone>& telephone)
{
	mRegisteredTelephones.insert(std::make_pair(telephone->getNativeNumber(), telephone));
	std::cout << "Telephone " << telephone->getNativeNumber() << " registered in station" << std::endl;
}

bool SwitchingCenter::isRegistered(const std::string& number)
{
	auto found = mRegisteredTelephones.find(number);
	if (found != std::cend(mRegisteredTelephones) && found->second.expired())
	{
		mRegisteredTelephones.erase(number);
		return false;
	}
	return found != std::cend(mRegisteredTelephones);
}

SwitchingCenter::ErrorState SwitchingCenter::getCallErrorState(const std::string& number)
{
	if (!isNumberValid(number))
	{
		return ErrorState::WrongNumber;
	}
	if (!isRegistered(number))
	{
		return ErrorState::Unregistered;
	}
	if (!mRegisteredTelephones.at(number).lock()->isInConnectionZone())
	{
		return ErrorState::OutOfZone;
	}
	if (mRegisteredTelephones.at(number).lock()->isBusy())
	{
		return ErrorState::Busy;
	}
	return None;
}

SwitchingCenter::ErrorState SwitchingCenter::getMessageErrorState(const std::string& number)
{
	if (!isNumberValid(number))
	{
		return ErrorState::WrongNumber;
	}
	if (!isRegistered(number))
	{
		return ErrorState::Unregistered;
	}
	if (!mRegisteredTelephones.at(number).lock()->isInConnectionZone())
	{
		return ErrorState::OutOfZone;
	}
	return None;
}

void SwitchingCenter::connect(Telephone& caller, const std::string& number)
{
	ErrorState error = getCallErrorState(number);
	if (error == ErrorState::None)
	{
		auto& receiver = *mRegisteredTelephones.at(number).lock();
		std::thread([&caller, &receiver]()
		{
			//std::this_thread::sleep_for(std::chrono::milliseconds(1000));
			std::cout << "You called " + receiver.getNativeNumber() << std::endl;
			receiver.getCall(caller.getNativeNumber());
			while (receiver.isGettingCall() && caller.isCalling()) { /* ожидание изменений из другого потока */ }
			if (receiver.isConnected())
			{
				caller.connect();
				std::cout << "Connection established! You are talking now" << std::endl;
				while (caller.isConnected() && receiver.isConnected()) { /* ожидание изменений из другого потока  */ }
				/* нужно отсоединить один телефон, но два тоже ок - последствий не будет */
				receiver.disconnect();
				caller.disconnect();
				std::cout << "Connection ended" << std::endl;
			}
			else
			{
				caller.disconnect();
				receiver.decline();
				std::cout << "Receiver rejected a call" << std::endl;
			}
		}).detach();
	}
	else if (error == ErrorState::OutOfZone)
	{
		mLateCalls[number].emplace_back(RegisteredCall::State::Missed, caller.getNativeNumber(), getCurrentTime(), 0);
		std::cout << "Receiver's telephone is out of zone of connection" << std::endl;
		caller.disconnect();
	}
	else
	{
		printError(error);
		caller.disconnect();
	}
}

void SwitchingCenter::printError(ErrorState error)
{
	switch (error)
	{
		case ErrorState::Busy:
		{
			std::cout << "Receiver's telephone is busy" << std::endl;
			break;
		}
		case ErrorState::OutOfZone:
		{
			std::cout << "Receiver's telephone is out of zone of connection" << std::endl;
			break;
		}
		case ErrorState::Unregistered:
		{
			std::cout << "Receiver's telephone number is not in the base" << std::endl;
			break;
		}
		case ErrorState::WrongNumber:
		{
			std::cout << "Wrong input number" << std::endl;
			break;
		}
		default:
			break;
	}
}

bool SwitchingCenter::sendMessage(Telephone& sender, const std::string& number, const std::string& text)
{
	ErrorState error = getMessageErrorState(number);
	if (error == ErrorState::None)
	{
		auto& receiver = *mRegisteredTelephones.at(number).lock();
		receiver.getMessage(sender.getNativeNumber(), text);
		return true;
	}
	else if (error == ErrorState::OutOfZone)
	{
		mLateMessages[number].emplace_back(Message::State::Imcoming, sender.getNativeNumber(), getCurrentTime(), text);
		std::cout << "Receiver's telephone is out of zone of connection, but message was sent" << std::endl;
		return true;
	}
	else
	{
		printError(error);
		return false;
	}
}

bool SwitchingCenter::isNumberValid(const std::string& number) const
{
	if (number.size() > sMaxNumberDigits)
	{
		return false;
	}
	std::regex r("\\+?[\\d\\#\\*]{1,}");
	return std::regex_match(number, r);
}

std::vector<RegisteredCall> SwitchingCenter::getLateCalls(const std::string& number)
{
	auto found = mLateCalls.find(number);
	if (found != cend(mLateCalls))
	{
		auto retval = found->second;
		mLateCalls.erase(number);
		return retval;
	}
	return std::vector<RegisteredCall>();
}

std::vector<Message> SwitchingCenter::getLateMessages(const std::string& number)
{
	auto found = mLateMessages.find(number);
	if (found != cend(mLateMessages))
	{
		auto retval = found->second;
		mLateMessages.erase(number);
		return retval;
	}
	return std::vector<Message>();
}