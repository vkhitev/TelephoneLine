#pragma once

#include "State.h"
#include "Container.h"
#include "Button.h"
#include "Label.h"

#include <SFML/Graphics/RectangleShape.hpp>

class Telephone;

class TelephoneState : public State
{
public:
	TelephoneState(StateStack& stack, AppContext context, Telephone& parent);
	virtual ~TelephoneState();

	virtual void draw() const override;
	virtual bool update(sf::Time dt) override;
	virtual bool handleEvent(const sf::Event& event) override;

protected:
	std::shared_ptr<GUI::Button> makeButton(const sf::Vector2f& size, const sf::Vector2f& position,
		const std::string& text, GUI::Button::Callback callback = nullptr);

	std::shared_ptr<GUI::Label> makeLabel(const sf::Vector2f& position, const std::string& text,
		const unsigned int fontSize, bool centralize = true);

protected:
	Telephone&			mTelephone;
	GUI::Container		mContainer;
	sf::RectangleShape	mBackgroundShape;
};