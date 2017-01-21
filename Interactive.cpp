#include "Interactive.h"

namespace GUI
{
	Interactive::Interactive()
		: mActions()
		, mIsFocused(false)
		, mIsMouseEntered(false)
		, mIsActive(true)
	{
		mActions[Left].triggerButton = sf::Mouse::Button::Left;
		mActions[Right].triggerButton = sf::Mouse::Button::Right;
		mActions[Middle].triggerButton = sf::Mouse::Button::Middle;
	}

	void Interactive::onHover(Callback callback)
	{
		mActions[Hover].callback = std::move(callback);
	}

	void Interactive::onFocusGain(Callback callback)
	{
		mActions[FocusGain].callback = std::move(callback);
	}

	void Interactive::onFocusLoose(Callback callback)
	{
		mActions[FocusLoose].callback = std::move(callback);
	}

	void Interactive::onMouseEnter(Callback callback)
	{
		mActions[MouseEnter].callback = std::move(callback);
	}

	void Interactive::onMouseLeave(Callback callback)
	{
		mActions[MouseLeave].callback = std::move(callback);
	}

	void Interactive::onLeftClick(Callback callback)
	{
		mActions[Left].callback = std::move(callback);
	}

	void Interactive::onRightClick(Callback callback)
	{
		mActions[Right].callback = std::move(callback);
	}

	void Interactive::onMiddleClick(Callback callback)
	{
		mActions[Middle].callback = std::move(callback);
	}

	void Interactive::setFocused(bool focused)
	{
		mIsFocused = focused;
		if (mIsFocused && mActions[FocusGain].callback)
		{
			mActions[FocusGain].callback();
		}
	}

	bool Interactive::isFocused() const
	{
		return mIsFocused;
	}

	void Interactive::setActive(bool active)
	{
		mIsActive = active;
	}

	bool Interactive::isActive() const
	{
		return mIsActive;
	}

	void Interactive::handleEvent(sf::RenderWindow& window, const sf::Event& event)
	{
		if (mIsActive && isMouseOver(window))
		{
			if (!mIsMouseEntered && mActions[MouseEnter].callback)
			{
				mIsMouseEntered = true;
				mActions[MouseEnter].callback();
			}

			if (event.type == sf::Event::MouseButtonPressed)
			{
				mActions[Left].isPressed = sf::Mouse::isButtonPressed(mActions[Left].triggerButton);
				mActions[Right].isPressed = sf::Mouse::isButtonPressed(mActions[Right].triggerButton);
				mActions[Middle].isPressed = sf::Mouse::isButtonPressed(mActions[Middle].triggerButton);

				if (!mIsFocused && mActions[FocusGain].callback)
				{
					mIsFocused = true;
					mActions[FocusGain].callback();
				}
			}

			else if (event.type == sf::Event::MouseButtonReleased)
			{
				for (auto& pair : mActions)
				{
					auto& value = pair.second;
					if (!sf::Mouse::isButtonPressed(value.triggerButton) &&
						value.isPressed &&
						value.callback)
					{
						value.isPressed = false;
						value.callback();
						break;
					}
				}
			}
		}
		else if (event.type == sf::Event::MouseButtonPressed)
		{
			if (mIsFocused && mActions[FocusLoose].callback)
			{
				mIsFocused = false;
				mActions[FocusLoose].callback();
			}
		}
		else if (mIsMouseEntered && mActions[MouseLeave].callback)
		{
			mIsMouseEntered = false;
			mActions[MouseLeave].callback();
		}
	}

	void Interactive::updateHover(sf::RenderWindow& window, sf::Time dt)
	{
		if (mIsActive && mActions[Hover].callback && isMouseOver(window))
			mActions[Hover].callback();
	}

	bool Interactive::isMouseOver(const sf::FloatRect& bounds, sf::RenderWindow& window) const
	{
		auto mousePosition = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
		return bounds.contains(mousePosition);
	}

	bool Interactive::isMouseOver(const sf::IntRect& bounds, sf::RenderWindow& window) const
	{
		auto mousePosition = sf::Mouse::getPosition(window);
		return bounds.contains(mousePosition);
	}

	Interactive::CallbackStruct::CallbackStruct()
		: callback(nullptr)
		, isPressed(false)
		, triggerButton(sf::Mouse::ButtonCount)
	{
	}
}