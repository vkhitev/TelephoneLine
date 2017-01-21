/**
*
* \class Component
*
* \brief Абстрактный класс для объектов пользовательского интерфейса
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

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>

#include <memory>


namespace sf
{
	class Event;
}

namespace GUI
{

	class Component : public sf::Drawable, public sf::Transformable
	{
	public:
		typedef std::shared_ptr<Component> Ptr;

	public:
		Component();
		virtual	~Component();

		virtual void update(sf::Time dt) = 0;
		virtual void handleEvent(const sf::Event& event) = 0;		
	};

}