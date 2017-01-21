#pragma once

#include "TelephoneState.h"
#include "InputField.h"

class TelephoneAddContactState final : public TelephoneState
{
public:
	TelephoneAddContactState(StateStack& stack, AppContext context, Telephone& mParent);

	virtual void draw() const override;
	virtual bool update(sf::Time dt) override;
	virtual bool handleEvent(const sf::Event& event) override;

private:
	GUI::InputField mInputFirstName;
	GUI::InputField mInputLastName;
};