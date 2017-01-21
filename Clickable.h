/**
*
* \class Clickable
*
* \brief На объекты классов наследников можно нажимать - будет вызвана определенная функция.
*
* Наследуется от Hoverable, поэтому требует переопределения метода "bool isMouseOver() const"
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

#include "Hoverable.h"

#include <SFML/Window/Event.hpp>
#include <functional>

class Clickable : public Hoverable
{
public:
	typedef std::function<void()> Callback;

	Clickable(sf::RenderWindow& window);

	/// Установить функцию обратного вызова
	/// \param callback Функция обратного вызова
	void setCallback(Callback callback);

	/// Получить функцию обратного вызова
	/// \return Функция обратного вызова
	Callback getCallback() const;

	/// Установить кнопку активации
	/// \param type Кнопка активации
	void setActivationButton(sf::Mouse::Button type);

	/// Получить кнопку активации
	/// \return Кнопка активации
	sf::Mouse::Button getActivationButton() const;

	/// Активация при нажатии или при отпускании кнопки
	/// \param flag true - активация при отпускании кнопки
	void setActivateByRelease(bool flag);

	/// Активировать при отпускании кнопки?
	/// \return true - активация при отпускании кнопки
	bool isActivatingByRelease() const;

	/// Можно ли нажимать на кнопку
	/// \param flag true - кнопка активная
	void setClickActive(bool flag);

	/// Можно ли нажимать на кнопку
	/// \return true - кнопка активна
	bool isClickActive() const;

protected:
	/// Нажата ли кнопка
	/// \return true - кнопка нажата
	bool isPressed() const;

	/// Попробовать активировать кнопку
	/// Метод должен вызываться в классе-наследнике
	/// \param event Входящее событие
	/// \param isMouseOver Наведена ли мышь на кнопку
	void tryActivate(const sf::Event& event, bool isMouseOver);

	/// Функция, которая по умолчанию будет вызываться при нажатии на кнопку
	virtual void defaultClickAction() { }

private:
	Callback mCallback;

	bool mIsClickActive;
	bool mIsPressed;

	sf::Mouse::Button mActivationButton;
	bool mActivateByRelease;
};