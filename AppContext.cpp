#include "AppContext.h"

#include <SFML/Graphics/RenderWindow.hpp>

AppContext::AppContext(sf::RenderWindow& window, TextureHolder& textures, FontHolder& fonts)
	: mWindow(window)
	, mTextures(textures)
	, mFonts(fonts)
{
}

sf::RenderWindow& AppContext::getWindow()
{
	return mWindow;
}

TextureHolder& AppContext::getTextures()
{
	return mTextures;
}

FontHolder& AppContext::getFonts()
{
	return mFonts;
}