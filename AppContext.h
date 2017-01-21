/**
*
* \class AppContext
*
* \brief Необходим для передачи окна, текстур и шрифтов между объектами других классов.
*
* \author Хитёв Владислав
*
* \version 8.0
*
* \date 2015/12/23
*
* Contact: vkhitev@gmail.com
*
*/

#pragma once

#include "ResourceHolder.h"
#include "ResourceIdentifiers.h"

namespace sf
{
	class RenderWindow;
}

class AppContext
{
public:
	AppContext(sf::RenderWindow& window, TextureHolder& textures, FontHolder& fonts);

	sf::RenderWindow& getWindow();
	TextureHolder& getTextures();
	FontHolder& getFonts();

private:
	sf::RenderWindow&	mWindow;
	TextureHolder&		mTextures;
	FontHolder&			mFonts;
};