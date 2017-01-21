#include "Hoverable.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Mouse.hpp>

Hoverable::Hoverable(sf::RenderWindow& window)
	: mWindow(window)
	, mIsHoverActive(true)
{

}

void Hoverable::setHoverActive(bool flag)
{
	mIsHoverActive = flag;
}

bool Hoverable::isHoverActive() const
{
	return mIsHoverActive;
}

bool Hoverable::isMouseOver(const sf::FloatRect& bounds) const
{
	auto mousePosition = static_cast<sf::Vector2f>(sf::Mouse::getPosition(mWindow));
	return bounds.contains(mousePosition);
}