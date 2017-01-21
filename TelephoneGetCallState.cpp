#include "TelephoneGetCallState.h"
#include "Telephone.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include <cassert>

const sf::Color    TelephoneGetCallState::BackgroundFillColor = { 31, 31, 31, 240 };
const sf::Vector2f TelephoneGetCallState::ButtonAcceptSize = { 100.f, 40.f };
const sf::Vector2f TelephoneGetCallState::ButtonAcceptPosition = { 35.f, 350.f };
const sf::Color    TelephoneGetCallState::ButtonAcceptOverTextColor = { 185, 122, 87 };
const sf::Vector2f TelephoneGetCallState::ButtonDeclineSize = { 100.f, 40.f };
const sf::Vector2f TelephoneGetCallState::ButtonDeclinePosition = { 230.f, 350.f };
const sf::Color    TelephoneGetCallState::ButtonDeclineOverTextColor = { 185, 122, 87 };
const sf::Vector2f TelephoneGetCallState::LabelIncommingCallPosition = { 175.f, 135.f };
const sf::Vector2f TelephoneGetCallState::LabelCallerPosition = { 175.f, 180.f };

TelephoneGetCallState::TelephoneGetCallState(StateStack& stack, AppContext context, Telephone& parent)
	: TelephoneState(stack, context, parent)
{
	assert(mTelephone.isGettingCall() && "Telephone is not getting call");

	mBackgroundShape.setFillColor(BackgroundFillColor);

	auto accept = makeButton(ButtonAcceptSize, ButtonAcceptPosition, "accept", [this]()
	{
		mTelephone.accept();
		requestStackPop();
	});
	accept->setOverTextColor(ButtonAcceptOverTextColor);

	auto decline = makeButton(ButtonDeclineSize, ButtonDeclinePosition, "decline", [this]()
	{
		mTelephone.decline();
		requestStackPop();
	});
	decline->setOverTextColor(ButtonDeclineOverTextColor);

	auto incomingCall = makeLabel(LabelIncommingCallPosition, "Incoming call", 29U);
	auto caller = makeLabel(LabelCallerPosition, mTelephone.getCaller(), 36U);

	

	mContainer.pack(accept);
	mContainer.pack(decline);
	mContainer.pack(incomingCall);
	mContainer.pack(caller);
}

void TelephoneGetCallState::draw() const
{
	auto& window = getContext().getWindow();
	window.draw(mBackgroundShape);
	mContainer.draw();
}

bool TelephoneGetCallState::update(sf::Time dt)
{
	if (!mTelephone.isGettingCall())
	{
		requestStackPop();
	}
	mContainer.update(dt);
	return false; // ! important
}

bool TelephoneGetCallState::handleEvent(const sf::Event& event)
{
	mContainer.handleEvent(event);
	return false;
}