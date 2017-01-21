#include "TelephoneAddContactState.h"
#include "Telephone.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include <cassert>

TelephoneAddContactState::TelephoneAddContactState(StateStack& stack, AppContext context, Telephone& parent)
	: TelephoneState(stack, context, parent)
	, mInputFirstName({ 0, 0 }, { 250, 60 }, context.getFonts().get(Fonts::Main), 25U)
	, mInputLastName({ 0, 0 }, { 250, 60 }, context.getFonts().get(Fonts::Main), 25U)
{
	auto& pos = mTelephone.getPosition();
	mInputFirstName.setPosition(sf::Vector2f(25, 200) + pos);
	mInputLastName.setPosition(sf::Vector2f(25, 310) + pos);

	mBackgroundShape.setFillColor({ 31, 31, 31, 240 });

	auto accept = makeButton({ 100.f, 40.f }, { 55.f, 400.f }, "add contact", [this]()
	{
		auto firstName = mInputFirstName.getString().toAnsiString();
		auto lastName = mInputLastName.getString().toAnsiString();
		if (!firstName.empty() && !lastName.empty())
		{
			mTelephone.addContact(firstName, lastName, mTelephone.getDialedNumber());
			requestStackPop();
		}
	});
	accept->setOverTextColor({ 185, 122, 87 });

	auto back = makeButton({ 100.f, 40.f }, { 230.f, 400.f }, "back", [this]()
	{
		requestStackPop();
	});
	back->setOverTextColor({ 185, 122, 87 });

	auto label = makeLabel({ 175.f, 135.f }, "Enter first and last name", 29U);

	mContainer.pack(accept);
	mContainer.pack(label);
	mContainer.pack(back);
}

void TelephoneAddContactState::draw() const
{
	auto& window = getContext().getWindow();
	window.draw(mBackgroundShape);
	window.draw(mInputFirstName);
	window.draw(mInputLastName);
	mContainer.draw();
}

bool TelephoneAddContactState::update(sf::Time dt)
{
	mInputFirstName.updateHover(getContext().getWindow(), dt);
	mInputLastName.updateHover(getContext().getWindow(), dt);
	mContainer.update(dt);
	return false; // ! important
}

bool TelephoneAddContactState::handleEvent(const sf::Event& event)
{
	mInputFirstName.handleEvent(getContext().getWindow(), event);
	mInputLastName.handleEvent(getContext().getWindow(), event);
	mContainer.handleEvent(event);
	return false;
}