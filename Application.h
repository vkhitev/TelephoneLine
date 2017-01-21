/**
*
* \class Application
*
* \brief Содержит окно, текстуры и шрифты.
* Здесь происходит основной цикл process -> update -> render.
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

#include "TelephoneLine.h"
#include "ResourceHolder.h"
#include "ResourceIdentifiers.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/System/NonCopyable.hpp>

#include <memory>

class Application : private sf::NonCopyable
{
public:
	Application(const std::string& firstNumber, const std::string& secondNumber);

	void run();

private:
	void processInput();
	void update(sf::Time dt);
	void render();

private:
	static const sf::Time TimePerFrame;

	sf::RenderWindow mWindow;
	TextureHolder	 mTextures;
	FontHolder		 mFonts;

	std::unique_ptr<TelephoneLine> mTelephoneLine;
};