#include "TelephoneState.h"
#include "Telephone.h"

#include <SFML/Graphics/RenderWindow.hpp>

TelephoneState::TelephoneState(StateStack& stack, AppContext context, Telephone& parent)
	: State(stack, context)
	, mTelephone(parent)
	, mContainer(context.getWindow())
	, mBackgroundShape(mTelephone.getSize())
{
	mBackgroundShape.setPosition(mTelephone.getPosition());
	mBackgroundShape.setOutlineThickness(1.f);
	mBackgroundShape.setOutlineColor(sf::Color::Black);
	mBackgroundShape.setFillColor({ 31, 31, 31 });
}

TelephoneState::~TelephoneState()
{
}

void TelephoneState::draw() const
{
	auto& window = getContext().getWindow();
	window.draw(mBackgroundShape);
	mContainer.draw();
}

bool TelephoneState::update(sf::Time dt)
{
	mContainer.update(dt);
	if (mTelephone.isGettingCall())
	{
		requestStackPush(States::GetCall);
	}
	return true;
}

bool TelephoneState::handleEvent(const sf::Event& event)
{
	mContainer.handleEvent(event);
	return true;
}

std::shared_ptr<GUI::Button> TelephoneState::makeButton(const sf::Vector2f& size,
	const sf::Vector2f& position, const std::string& text, GUI::Button::Callback callback)
{
	auto button = std::make_unique<GUI::Button>(getContext());
	button->setPosition(position + mTelephone.getPosition());
	button->setSize(size);
	button->setText(text);
	button->setCallback(callback);
	return std::move(button);
}

std::shared_ptr<GUI::Label> TelephoneState::makeLabel(const sf::Vector2f& position,
	const std::string& text, const unsigned int fontSize, bool centralize)
{
	auto label = std::make_unique<GUI::Label>(getContext().getFonts().get(Fonts::Main), "", fontSize, centralize);
	label->setPosition(position + mTelephone.getPosition());
	label->setString(text);
	return std::move(label);
}