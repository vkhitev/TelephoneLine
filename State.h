/**
*
* \class State
*
* \brief ����������� ����� "���������" ������� ��� ��������� � �����.
*
* �������������� ������ ���������� ���� ���������� ��������� (����) �������.
* ��� ����������� ��������� � ���������, ����� ������������ � �������������� ����������.
* ������������ ����� ������������, ������� ���� (�������) ������������ ������� � �����������.
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
	/// ������ ����� ���������
	/// \param stack ���� ���������
	/// \param context ����������� ��������
	State(StateStack& stack, AppContext context);
	virtual ~State() = default;

	/// ���������� ���� �� ������
	virtual void draw() const = 0;

	/// �������� ����
	/// \return false, ���� ��� ���� ���� �� ������ �����������
	virtual bool update(sf::Time dt) = 0;

	/// ���������� �������� �������
	/// \return false, ���� ��� ���� ���� �� ������ ��������������
	virtual bool handleEvent(const sf::Event& event) = 0;

protected:
	/// �������� ����� ��������� � ����
	/// \param stateID ������������� ���������
	void requestStackPush(States::ID stateID);

	/// ������� ������� ��������� �� �����
	void requestStackPop();

	/// �������� ���� ���������
	void requestStateClear();

	/// �������� ����������� ��������
	/// \return ����������� �������� ���������
	AppContext getContext() const;

private:
	/// ���� ���������
	StateStack* mStack;

	/// ����������� �������� ���������
	AppContext mContext;
};