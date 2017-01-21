#include "TelephoneLine.h"
#include "Telephone.h"
#include "SwitchingCenter.h"

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include <memory>
#include <iostream>

const sf::Vector2f TelephoneLine::TelephoneSize = { 350.f, 560.f };
const sf::Vector2f TelephoneLine::Telephone1Position = { 75, 120 };
const sf::Vector2f TelephoneLine::Telephone2Position = { 855, 120 };

TelephoneLine::TelephoneLine(AppContext context, const std::string& firstNumber, const std::string& secondNumber)
	: mSwitchingCenter(std::make_shared<SwitchingCenter>(context))
	, mTelephone1(std::make_shared<Telephone>(context, firstNumber, *this))
	, mTelephone2(std::make_shared<Telephone>(context, secondNumber, *this))
	, mWindow(context.getWindow())
	, mBackground(context.getTextures().get(Textures::Background))
{
	std::cout << "Telephone line created" << std::endl;

	mTelephone1->setPosition(Telephone1Position);
	mTelephone2->setPosition(Telephone2Position);

	mTelephone1->setSize(TelephoneSize);
	mTelephone2->setSize(TelephoneSize);

	mTelephone1->addContact("Petya", "Petin", "12345");
	mTelephone1->addContact("Unknown", "Contact", "444332");
	mTelephone1->addContact("Vlad", "Khitev", "0678824771");

	mTelephone2->addContact("Vasya", "Pupkin", "228");
	mTelephone2->addContact("Test", "Test", "0978199913");
	mTelephone1->addContact("Tatyana", "Kovaluk", "0502271172");

	mSwitchingCenter->registerTelephone(mTelephone1);
	mSwitchingCenter->registerTelephone(mTelephone2);
}

void TelephoneLine::handleEvent(const sf::Event& event)
{
	mTelephone1->handleEvent(event);
	mTelephone2->handleEvent(event);
}

void TelephoneLine::update(sf::Time dt)
{
	mTelephone1->update(dt);
	mTelephone2->update(dt);
}

void TelephoneLine::draw() const
{
	mWindow.draw(mBackground);
	mTelephone1->draw();
	mTelephone2->draw();
}

std::shared_ptr<SwitchingCenter> TelephoneLine::getSwitchingCenter() const
{
	return mSwitchingCenter;
}