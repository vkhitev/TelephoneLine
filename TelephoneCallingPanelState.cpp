#include "TelephoneCallingPanelState.h"
#include "Telephone.h"

#include <vector>

using namespace GUI;

const sf::Vector2f TelephoneCallingPanelState::ButtonSize = { 105.f, 61.f };
const sf::Vector2f TelephoneCallingPanelState::ButtonPanelOffset = { 14.f, 165.f };
const sf::Vector2f TelephoneCallingPanelState::XButtonOffset = { 110.f, 0.f };
const sf::Vector2f TelephoneCallingPanelState::YButtonOffset = { 0.f, 66.f };
const sf::Vector2f TelephoneCallingPanelState::TextCenterOffset = { 175.f, 87.f };

TelephoneCallingPanelState::TelephoneCallingPanelState(StateStack& stack, AppContext context, Telephone& parent)
	: TelephoneState(stack, context, parent)
{
	std::vector<std::string> texts {
		"1", "2", "3",
		"4", "5", "6",
		"7", "8", "9",
		"*", "0", "#",
		"add", "call", "del" };

	sf::Vector2f pos(0, 0);
	for (const std::string& text : texts)
	{
		sf::Vector2f offset = ButtonPanelOffset + (pos.x * XButtonOffset) + (pos.y * YButtonOffset);
		auto button = makeButton(ButtonSize, offset, text, std::bind(&TelephoneCallingPanelState::addElement, this, text));
		button->setBackgroundColor({ 57, 58, 60 });
		button->setUnactiveBackgroundColor({ 57, 58, 60 });
		button->setOverBackgroundColor({ 185, 122, 87 });
		button->setUnactiveTextColor({ 160, 160, 160 });
		mContainer.pack(text, button);
		if (++pos.x == 3)
		{
			pos.x = 0;
			pos.y++;
		}
	}
	
	auto display = makeLabel(TextCenterOffset, mTelephone.getDialedNumber(), 34U);
	mContainer.pack("display", display);

	mContainer.get<Button>("del")->setCallback(std::bind(&TelephoneCallingPanelState::removeElement, this));

	mContainer.get<Button>("add")->setCallback([this]()
	{
		requestStackPush(States::AddContact);
	});

	mContainer.get<Button>("call")->setCallback([this]()
	{
		if (mTelephone.isBusy())
			mTelephone.disconnect();
		else
			mTelephone.call();
	});

	mContainer.get<Button>("#")->setSize(ButtonSize.x / 2.f - 2.f, ButtonSize.y);

	sf::Vector2f offset = ButtonPanelOffset + (2.f * XButtonOffset) +
		(3.f * YButtonOffset) + sf::Vector2f(ButtonSize.x / 2.f + 2.f, 0);
	auto plus = makeButton(ButtonSize, offset, "+", std::bind(&TelephoneCallingPanelState::addElement, this, "+"));
	plus->setBackgroundColor({ 57, 58, 60 });
	plus->setUnactiveBackgroundColor({ 57, 58, 60 });
	plus->setOverBackgroundColor({ 185, 122, 87 });
	plus->setUnactiveTextColor({ 160, 160, 160 });
	plus->setSize(ButtonSize.x / 2.f - 2.f, ButtonSize.y);
	plus->setTextSize(45U);

	auto contacts = makeButton({ 100.f, 40.f }, { 25.f, 515.f }, "contacts", [this]()
	{
		requestStackPop();
		requestStackPush(States::ContactList);
	});
	contacts->setTextSize(22U);
	contacts->setOverTextColor({ 185, 122, 87 });
	mContainer.pack("contacts", contacts);

	if (mTelephone.getDialedNumber().empty())
	{
		mContainer.get<Button>("add")->setClickActive(false);
		mContainer.get<Button>("call")->setClickActive(false);
	}

	auto connection = makeButton({ 120.f, 40.f }, { 200.f, 25.f }, "connected", [this]()
	{
		auto connection = mContainer.get<Button>("connection");
		if (mTelephone.isInConnectionZone())
		{
			mTelephone.setSwicthingCenter(nullptr);
			connection->setText("not connected");
		}
		else
		{
			mTelephone.connectToNearestSwitchingCenter();
			connection->setText("connected");
		}
	});
	connection->setTextSize(22U);
	connection->setOverTextColor({ 185, 122, 87 });
	if (!mTelephone.isInConnectionZone())
	{
		connection->setText("not connected");
	}

	mContainer.pack(plus);
	mContainer.pack("connection", connection);
}

bool TelephoneCallingPanelState::update(sf::Time dt)
{
	auto callButton = mContainer.get<Button>("call");
	if (mTelephone.isBusy() && callButton->getText() == "call")
	{
		callButton->setText("disc");
		callButton->setClickActive(true);
	}
	else if (!mTelephone.isBusy() && callButton->getText() == "disc")
	{
		callButton->setText("call");
		if (!mTelephone.getDialedNumber().empty())
			callButton->setClickActive(true);
	}

	TelephoneState::update(dt);
	return true;
}

bool TelephoneCallingPanelState::handleEvent(const sf::Event& event)
{
	mContainer.handleEvent(event);
	return true;
}

void TelephoneCallingPanelState::addElement(const std::string& element)
{
	auto display = mContainer.get<Label>("display");
	auto add = mContainer.get<Button>("add");
	auto call = mContainer.get<Button>("call");

	std::string number = mTelephone.getDialedNumber();
	if (number.length() < 13)
	{
		number += element;
		mTelephone.setDialedNumber(number);
		display->setString(number);
	}

	if (!add->isClickActive())
	{
		add->setClickActive(true);
		if (call->getText() == "call")
			call->setClickActive(true);
	}
}

void TelephoneCallingPanelState::removeElement()
{
	auto display = mContainer.get<Label>("display");
	auto add = mContainer.get<Button>("add");
	auto call = mContainer.get<Button>("call");

	std::string number = mTelephone.getDialedNumber();
	if (!number.empty())
	{
		number.pop_back();
		mTelephone.setDialedNumber(number);
		display->setString(number);
	}

	if (number.empty())
	{
		add->setClickActive(false);
		if (call->getText() == "call")
			call->setClickActive(false);
	}
}