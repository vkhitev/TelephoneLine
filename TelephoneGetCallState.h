#pragma once

#include "TelephoneState.h"

class TelephoneGetCallState final : public TelephoneState
{
public:
	TelephoneGetCallState(StateStack& stack, AppContext context, Telephone& mParent);

	virtual void draw() const override;
	virtual bool update(sf::Time dt) override;
	virtual bool handleEvent(const sf::Event& event) override;

private:
	static const sf::Color    BackgroundFillColor;
	static const sf::Vector2f ButtonAcceptSize;
	static const sf::Vector2f ButtonAcceptPosition;
	static const sf::Color    ButtonAcceptOverTextColor;
	static const sf::Vector2f ButtonDeclineSize;
	static const sf::Vector2f ButtonDeclinePosition;
	static const sf::Color    ButtonDeclineOverTextColor;
	static const sf::Vector2f LabelIncommingCallPosition;
	static const sf::Vector2f LabelCallerPosition;
};