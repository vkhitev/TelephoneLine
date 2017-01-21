#include "Clickable.h"

#include <SFML/Window/Mouse.hpp>

Clickable::Clickable(sf::RenderWindow& window)
	: Hoverable(window)
	, mCallback()
	, mIsClickActive(true)
	, mIsPressed(false)
	, mActivationButton(sf::Mouse::Button::Left)
	, mActivateByRelease(true)
{
}

void Clickable::setCallback(Callback callback)
{
	mCallback = std::move(callback);
}

Clickable::Callback Clickable::getCallback() const
{
	return mCallback;
}

void Clickable::setActivationButton(sf::Mouse::Button type)
{
	mActivationButton = type;
}

sf::Mouse::Button Clickable::getActivationButton() const
{
	return mActivationButton;
}

void Clickable::setActivateByRelease(bool flag)
{
	mActivateByRelease = flag;
}

bool Clickable::isActivatingByRelease() const
{
	return mActivateByRelease;
}

void Clickable::setClickActive(bool flag)
{
	mIsClickActive = flag;
}

bool Clickable::isClickActive() const
{
	return mIsClickActive;
}

bool Clickable::isPressed() const
{
	return mIsPressed;
}

void Clickable::tryActivate(const sf::Event& event, bool isMouseOver)
{
	if (!mIsClickActive)
	{
		return;
	}

	if (isMouseOver)
	{
		if (event.type == sf::Event::MouseButtonPressed &&
			sf::Mouse::isButtonPressed(mActivationButton))
		{
			if (mActivateByRelease) /* активация после отжатия */
			{
				mIsPressed = true;
			}
			else if (mCallback) /* активация сразу при нажатии */
			{
				mCallback();
			}
		}
		else if (event.type == sf::Event::MouseButtonReleased && mIsPressed)
		{
			mIsPressed = false;
			if (mCallback)
			{
				mCallback();
			}
		}
	}
	else /* отжать, если мышь уходит за пределы кнопки */
	{
		mIsPressed = false;
	}
}