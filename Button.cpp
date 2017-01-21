#include "Button.h"
#include "Utility.h"
#include "ResourceIdentifiers.h"
#include "ResourceHolder.h"

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

namespace GUI
{
	Button::Button(AppContext context)
		: Clickable(context.getWindow())
		, mShape()
		, mText("", context.getFonts().get(Fonts::Main), 30)
		, mBackgroundColor(sf::Color::Transparent)
		, mTextColor(sf::Color::White)
		, mOutlineColor(sf::Color::Transparent)
		, mOverBackgroundColor(sf::Color::Transparent)
		, mOverTextColor(sf::Color::White)
		, mOverOutlineColor(sf::Color::Transparent)
		, mUnactiveBackgroundColor(sf::Color::Transparent)
		, mUnactiveOverTextColor(sf::Color::White)
		, mUnactiveOverOutlineColor(sf::Color::Transparent)
	{
		mShape.setOutlineThickness(0);
		updateTextPosition();
	}

	void Button::setText(const std::string& text)
	{
		mText.setString(text);
		updateTextPosition();
	}

	void Button::setTextSize(const unsigned int size)
	{
		mText.setCharacterSize(size);
		updateTextPosition();
	}

	void Button::setSize(const sf::Vector2f& size)
	{
		mShape.setSize(size);
		updateTextPosition();
	}

	void Button::setSize(float x, float y)
	{
		setSize(sf::Vector2f(x, y));
	}

	void Button::setFont(sf::Font& font)
	{
		mText.setFont(font);
		updateTextPosition();
	}

	void Button::setBackgroundColor(const sf::Color& color)
	{
		mBackgroundColor = color;
		mShape.setFillColor(color);
	}

	void Button::setTextColor(const sf::Color& color)
	{
		mTextColor = color;
		mText.setColor(color);
	}

	void Button::setOutlineThickness(float thickness)
	{
		mShape.setOutlineThickness(thickness);
	}

	void Button::setOutlineColor(const sf::Color& color)
	{
		mOutlineColor = color;
		mShape.setOutlineColor(color);
	}

	void Button::setOverBackgroundColor(const sf::Color& color)
	{
		mOverBackgroundColor = color;
	}

	void Button::setOverTextColor(const sf::Color& color)
	{
		mOverTextColor = color;
	}

	void Button::setOverOutlineColor(const sf::Color& color)
	{
		mOverOutlineColor = color;
	}

	void Button::setUnactiveBackgroundColor(const sf::Color& color)
	{
		mUnactiveBackgroundColor = color;
	}

	void Button::setUnactiveTextColor(const sf::Color& color)
	{
		mUnactiveOverTextColor = color;
	}

	void Button::setUnactiveOutlineColor(const sf::Color& color)
	{
		mUnactiveOverOutlineColor = color;
	}

	std::string Button::getText() const
	{
		return mText.getString();
	}

	void Button::handleEvent(const sf::Event& event)
	{
		tryActivate(event, isMouseOver());
	}

	void Button::update(sf::Time dt)
	{
		if (isMouseOver() && isHoverActive() && isClickActive())
		{
			defaultHoverAction();
			mText.setColor(mOverTextColor);
			mShape.setFillColor(mOverBackgroundColor);
			mShape.setOutlineColor(mOverOutlineColor);
		}
		else if (isClickActive())
		{
			mText.setColor(mTextColor);
			mShape.setFillColor(mBackgroundColor);
			mShape.setOutlineColor(mOutlineColor);
		}
		else /* кнопка неактивна */
		{
			mText.setColor(mUnactiveOverTextColor);
			mShape.setFillColor(mUnactiveBackgroundColor);
			mShape.setOutlineColor(mUnactiveOverOutlineColor);
		}
		if (isPressed())
		{
			defaultClickAction();
		}
	}

	void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();
		target.draw(mShape, states);
		target.draw(mText, states);
	}

	void Button::updateTextPosition()
	{
		sf::FloatRect bounds = mShape.getLocalBounds();
		sf::Vector2f size(bounds.width, bounds.height);
		if (size.x > 0 && size.y > 0 && !mText.getString().isEmpty())
		{
			centerOrigin(mText);
			mText.setPosition(size.x / 2, size.y / 2);
		}
	}

	bool Button::isMouseOver() const
	{
		sf::FloatRect bounds(getPosition(), mShape.getSize());
		return Hoverable::isMouseOver(bounds);
	}
}