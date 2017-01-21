/**
*
* \class StateStack
*
* \brief Стек, содержащий состояния системы. Позволяет управлять ими.
*
* Позволяет добавлять и удалять состояния (слои). Перед вызовом состояния,
* его необходимо предварительно зарегестрировать в этом стеке. 
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

#include "State.h"
#include "StateIdentifiers.h"
#include "ResourceIdentifiers.h"
#include "AppContext.h"

#include <SFML/System/NonCopyable.hpp>
#include <SFML/System/Time.hpp>

#include <vector>
#include <utility>
#include <functional>
#include <map>

namespace sf
{
	class Event;
	class RenderWindow;
}

class StateStack : private sf::NonCopyable
{
public:
	enum Action
	{
		Push,
		Pop,
		Clear,
	};

public:
	/// Создаёт стек
	/// \param context Графический контекст программы
	explicit StateStack(AppContext context);

	/// Зарегестрировать состояние
	/// \param stateID Идентификатор состояния
	template <typename T>
	void registerState(States::ID stateID);

	/// Зарегестрировать состояние
	/// \param stateID Идентификатор состояния
	/// \param param1 Дополнительный параметр
	template <typename T, typename Param1>
	void registerState(States::ID stateID, Param1& param1);

	/// Отобразить слои на экране
	void draw() const;

	/// Обновить состояния в стеке
	void update(sf::Time dt);

	/// Обработать входящие события состояний в стеке
	void handleEvent(const sf::Event& event);
	
	/// Добавить состояние в стек
	/// \param stateID Идентификатор состояния
	void pushState(States::ID stateID);

	/// Удалить верхнее состояние из стека
	void popState();

	/// Удалить все состояния из стека
	void clearStates();
	
	/// Пустой ли стек
	/// \return true, если стек пустой, иначе - false
	bool isEmpty() const;

private:
	State::Ptr createState(States::ID stateID);
	void applyPendingChanges();

private:
	struct PendingChange
	{
		explicit PendingChange(Action action, States::ID stateID = States::None);

		Action action;
		States::ID stateID;
	};


private:
	/// Стек состояний
	std::vector<State::Ptr>	mStack;

	/// Поскольку нельзя обновлять стек, пока происходит итерация по нему,
	/// состояния необходимо добавлять и удалять после полного прохождения.
	/// Этот массив содержит временные данные
	/// и очищается после каждого обновления стека
	std::vector<PendingChange> mPendingList;

	/// Графический контекст программы
	AppContext mContext;

	/// При добавлении состояния вызывается функция (конструктор состояния),
	/// Соответствующая идентификатору в данном массиве
	std::map<States::ID, std::function<State::Ptr()>> mFactories;
};


template <typename T>
void StateStack::registerState(States::ID stateID)
{
	mFactories[stateID] = [this]()
	{
		return State::Ptr(new T(*this, mContext));
	};
}

template <typename T, typename Param1>
void StateStack::registerState(States::ID stateID, Param1& param1)
{
	mFactories[stateID] = [this, &param1]()
	{
		return State::Ptr(new T(*this, mContext, param1));
	};
}