/**
*
* \class Hoverable
*
* \brief На объекты классов наследников можно наводить мышью - будет вызвана определенная функция.
*
* Требует переопределения метода "bool isMouseOver() const"
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

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class Hoverable
{
public:
	Hoverable(sf::RenderWindow& window);
	virtual ~Hoverable() = default;

	/// Установить активность при наведении мышью
	/// \param flag true - наведение активно
	void setHoverActive(bool flag);

	/// Активен ли объект при наведении
	/// \param flag true - наведение активно
	bool isHoverActive() const;

protected:
	bool isMouseOver(const sf::FloatRect& bounds) const;
	virtual void defaultHoverAction() { }

private:
	virtual bool isMouseOver() const = 0;

	sf::RenderWindow& mWindow;
	bool mIsHoverActive;
};