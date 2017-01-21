/**
*
* \class State
*
* \brief Абстрактный класс "состояния" системы или отдельной её части.
*
* Унаследованные классы определяют одно конкретное состояние (слой) системы.
* Они динамически создаются и удаляются, могут существовать в неограниченном количестве.
* Пользователь может регулировать, сколько слоёв (верхних) обрабатывают события и обновляются.
*
* \author SFML | Хитёв Владислав
*
* \copyright http://www.sfml-dev.org/
*
* \version 8.0
*
* \date 2015/12/23
*
* Contact: vkhitev@gmail.com
*
*/
#pragma once

#include "AppContext.h"
#include "StateIdentifiers.h"

#include <SFML/System/Time.hpp>

#include <memory>

namespace sf
{
	class RenderWindow;
	class Event;
}

class StateStack;

class State
{
public:
	typedef std::unique_ptr<State> Ptr;

public:
	/// Создаёт новое состояние
	/// \param stack Стек состояний
	/// \param context Графический контекст
	State(StateStack& stack, AppContext context);
	virtual ~State() = default;

	/// Отобразить слой на экране
	virtual void draw() const = 0;

	/// Обновить слой
	/// \return false, если все слои ниже не должны обновляться
	virtual bool update(sf::Time dt) = 0;

	/// Обработать входящее событие
	/// \return false, если все слои ниже не должны обрабатываться
	virtual bool handleEvent(const sf::Event& event) = 0;

protected:
	/// Добавить новое состояние в стек
	/// \param stateID Идентификатор состояния
	void requestStackPush(States::ID stateID);

	/// Удалить верхнее состояние из стека
	void requestStackPop();

	/// Очистить стек состояний
	void requestStateClear();

	/// Получить графический контекст
	/// \return Графический контекст программы
	AppContext getContext() const;

private:
	/// Стек состояний
	StateStack* mStack;

	/// Графический контекст программы
	AppContext mContext;
};