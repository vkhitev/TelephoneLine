#include "TelephoneContactState.h"
#include "Telephone.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include <cassert>

const sf::Color    TelephoneContactState::BackgroundFillColor = { 31, 31, 31 };
const sf::Vector2f TelephoneContactState::ButtonAcceptSize = { 100.f, 40.f };
const sf::Vector2f TelephoneContactState::ButtonAcceptPosition = { 35.f, 350.f };
const sf::Color    TelephoneContactState::ButtonAcceptOverTextColor = { 185, 122, 87 };
const sf::Vector2f TelephoneContactState::ButtonDeclineSize = { 100.f, 40.f };
const sf::Vector2f TelephoneContactState::ButtonDeclinePosition = { 230.f, 350.f };
const sf::Color    TelephoneContactState::ButtonDeclineOverTextColor = { 185, 122, 87 };
const sf::Vector2f TelephoneContactState::LabelCallerNamePosition = { 175.f, 135.f };
const sf::Vector2f TelephoneContactState::LabelCallerNumberPosition = { 175.f, 180.f };

TelephoneContactState::TelephoneContactState(StateStack& stack, AppContext context, Telephone& parent)
: TelephoneState(stack, context, parent)
{
	std::string callerNumber = mTelephone.getStateParam();
	mTelephone.setStateParam("");

	auto& contacts = mTelephone.getDataBase().getContacts();

	Contact contact = *std::find_if(cbegin(contacts), cend(contacts), [&callerNumber](const Contact& c)
	{
		return c.getNumber() == callerNumber;
	});

	mBackgroundShape.setFillColor(BackgroundFillColor);

	auto call = makeButton(ButtonAcceptSize, ButtonAcceptPosition, "call", [this, callerNumber]()
	{
		requestStackPop();
		requestStackPush(States::CallingPanel);
		mTelephone.setDialedNumber(callerNumber);
		mTelephone.call();
	});
	call->setOverTextColor(ButtonAcceptOverTextColor);

	auto back = makeButton(ButtonDeclineSize, ButtonDeclinePosition, "back", [this]()
	{
		mTelephone.decline();
		requestStackPop();
		requestStackPush(States::ContactList);
	});
	back->setOverTextColor(ButtonDeclineOverTextColor);

	auto changeContact = makeButton(ButtonAcceptSize, sf::Vector2f(130, 460.f),
									"Remove contact", [this, contact]()
	{
		mTelephone.removeContact(contact);
		requestStackPop();
		requestStackPush(States::ContactList);
	});
	changeContact->setOverTextColor(ButtonDeclineOverTextColor);

	auto incomingCall = makeLabel(LabelCallerNamePosition, contact.getFullName(), 29U);
	auto caller = makeLabel(LabelCallerNumberPosition, callerNumber, 36U);

	mContainer.pack(call);
	mContainer.pack(back);
	mContainer.pack(changeContact);
	mContainer.pack(incomingCall);
	mContainer.pack(caller);
}

void TelephoneContactState::draw() const
{
	auto& window = getContext().getWindow();
	window.draw(mBackgroundShape);
	mContainer.draw();
}

bool TelephoneContactState::update(sf::Time dt)
{
	mContainer.update(dt);
	return false; // ! important
}

bool TelephoneContactState::handleEvent(const sf::Event& event)
{
	mContainer.handleEvent(event);
	return false;
}