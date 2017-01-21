#include "Application.h"
#include "AppContext.h"

#include <SFML/Window/Event.hpp>

const sf::Time Application::TimePerFrame = sf::seconds(1.f / 60.f);

Application::Application(const std::string& firstNumber, const std::string& secondNumber)
	: mWindow(sf::VideoMode(1280, 800), "Telephone line", sf::Style::Close)
	, mTextures()
	, mFonts()
	, mTelephoneLine(nullptr)
{
	mWindow.setVerticalSyncEnabled(true);
	mWindow.setKeyRepeatEnabled(true);

	mFonts.load(Fonts::Main, "Media/Sansation.ttf");
	mTextures.load(Textures::Background, "Media/Textures/background5.jpg");

	AppContext context(mWindow, mTextures, mFonts);
	mTelephoneLine = std::make_unique<TelephoneLine>(std::move(context), firstNumber, secondNumber);
}

void Application::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	while (mWindow.isOpen())
	{
		sf::Time elapsedTime = clock.restart();
		timeSinceLastUpdate += elapsedTime;
		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;

			processInput();
			update(TimePerFrame);

		}
		render();
	}
}

void Application::processInput()
{
	sf::Event event;
	while (mWindow.pollEvent(event))
	{
		mTelephoneLine->handleEvent(event);

		//if (event.type == sf::Event::Closed || event.key.code == sf::Keyboard::Escape)
		//mWindow.close();

		if (event.type == sf::Event::Closed)
			mWindow.close();
	}
}

void Application::update(sf::Time dt)
{
	mTelephoneLine->update(dt);
}

void Application::render()
{
	mWindow.clear();
	mTelephoneLine->draw();
	mWindow.display();
}