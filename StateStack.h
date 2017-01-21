/**
*
* \class StateStack
*
* \brief ����, ���������� ��������� �������. ��������� ��������� ���.
*
* ��������� ��������� � ������� ��������� (����). ����� ������� ���������,
* ��� ���������� �������������� ���������������� � ���� �����. 
*
* \author SFML | ���� ���������
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
	/// ������ ����
	/// \param context ����������� �������� ���������
	explicit StateStack(AppContext context);

	/// ���������������� ���������
	/// \param stateID ������������� ���������
	template <typename T>
	void registerState(States::ID stateID);

	/// ���������������� ���������
	/// \param stateID ������������� ���������
	/// \param param1 �������������� ��������
	template <typename T, typename Param1>
	void registerState(States::ID stateID, Param1& param1);

	/// ���������� ���� �� ������
	void draw() const;

	/// �������� ��������� � �����
	void update(sf::Time dt);

	/// ���������� �������� ������� ��������� � �����
	void handleEvent(const sf::Event& event);
	
	/// �������� ��������� � ����
	/// \param stateID ������������� ���������
	void pushState(States::ID stateID);

	/// ������� ������� ��������� �� �����
	void popState();

	/// ������� ��� ��������� �� �����
	void clearStates();
	
	/// ������ �� ����
	/// \return true, ���� ���� ������, ����� - false
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
	/// ���� ���������
	std::vector<State::Ptr>	mStack;

	/// ��������� ������ ��������� ����, ���� ���������� �������� �� ����,
	/// ��������� ���������� ��������� � ������� ����� ������� �����������.
	/// ���� ������ �������� ��������� ������
	/// � ��������� ����� ������� ���������� �����
	std::vector<PendingChange> mPendingList;

	/// ����������� �������� ���������
	AppContext mContext;

	/// ��� ���������� ��������� ���������� ������� (����������� ���������),
	/// ��������������� �������������� � ������ �������
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