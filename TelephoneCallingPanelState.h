#pragma once

#include "TelephoneState.h"

class TelephoneCallingPanelState final : public TelephoneState
{
public:
	TelephoneCallingPanelState(StateStack& stack, AppContext context, Telephone& mParent);

	virtual bool update(sf::Time dt) override;
	virtual bool handleEvent(const sf::Event& event) override;

private:
	void addElement(const std::string& element);
	void removeElement();

private:
	static const sf::Vector2f ButtonSize;
	static const sf::Vector2f ButtonPanelOffset;
	static const sf::Vector2f XButtonOffset;
	static const sf::Vector2f YButtonOffset;
	static const sf::Vector2f TextCenterOffset;
};