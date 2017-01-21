/**
*
* \class TelephoneLine
*
* \brief Содержит информацию об СМС-сообщении
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

#include "Telephone.h"
#include "SwitchingCenter.h"
#include "AppContext.h"

#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/System/NonCopyable.hpp>
#include <SFML/Graphics/Sprite.hpp>

namespace sf
{
	class Event;
	class RenderWindow;
}

class TelephoneLine : private sf::NonCopyable
{
public:
	TelephoneLine(AppContext context, const std::string& firstNumber, const std::string& secondNumber);

	void handleEvent(const sf::Event& event);
	void update(sf::Time dt);
	void draw() const;

	std::shared_ptr<SwitchingCenter> getSwitchingCenter() const;

private:
	std::shared_ptr<SwitchingCenter>	mSwitchingCenter;
	std::shared_ptr<Telephone>			mTelephone1;
	std::shared_ptr<Telephone>			mTelephone2;

	sf::RenderWindow&					mWindow;
	sf::Sprite							mBackground;

	static const sf::Vector2f			TelephoneSize;
	static const sf::Vector2f			Telephone1Position;
	static const sf::Vector2f			Telephone2Position;
};