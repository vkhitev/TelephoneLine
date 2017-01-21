#include "Label.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <iostream>

#include "Utility.h"

namespace GUI
{

	Label::Label(sf::Font& font, const std::string& text, const unsigned int size, bool centralized)
		: mText(text, font, size)
		, mIsOriginCentralized(centralized)
	{
		mText.setColor(sf::Color::White);

		applyOrigin();
	}

	void Label::setText(const sf::Text& text)
	{
		mText = text;
		applyOrigin();
	}

	const sf::Text& Label::getText() const
	{
		return mText;
	}

	void Label::setString(const std::string& string)
	{
		mText.setString(string);
		applyOrigin();
	}

	std::string Label::getString() const
	{
		return mText.getString();
	}

	void Label::setCenterOrigin()
	{
		mIsOriginCentralized = true;
	}

	void Label::setDefaultOrigin()
	{
		mIsOriginCentralized = false;
	}

	void Label::applyOrigin()
	{
		if (mIsOriginCentralized)
		{
			sf::FloatRect bounds = mText.getLocalBounds();
			mText.setOrigin(std::floor(bounds.left + bounds.width / 2.f), std::floor(bounds.top + bounds.height / 2.f));
		}
		else
		{
			mText.setOrigin(sf::Vector2f(0, 0));
		}
	}

	void Label::setCharacterSize(const unsigned int size)
	{
		mText.setCharacterSize(size);
		applyOrigin();
	}

	void Label::setColor(const sf::Color& color)
	{
		mText.setColor(color);
		applyOrigin();
	}

	void Label::update(sf::Time dt)
	{
	}

	void Label::handleEvent(const sf::Event& event)
	{
	}

	void Label::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();
		target.draw(mText, states);
	}
}