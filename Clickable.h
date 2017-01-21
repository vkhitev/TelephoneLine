/**
*
* \class Clickable
*
* \brief �� ������� ������� ����������� ����� �������� - ����� ������� ������������ �������.
*
* ����������� �� Hoverable, ������� ������� ��������������� ������ "bool isMouseOver() const"
*
* \author ���� ���������
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

	/// ���������� ������� ��������� ������
	/// \param callback ������� ��������� ������
	void setCallback(Callback callback);

	/// �������� ������� ��������� ������
	/// \return ������� ��������� ������
	Callback getCallback() const;

	/// ���������� ������ ���������
	/// \param type ������ ���������
	void setActivationButton(sf::Mouse::Button type);

	/// �������� ������ ���������
	/// \return ������ ���������
	sf::Mouse::Button getActivationButton() const;

	/// ��������� ��� ������� ��� ��� ���������� ������
	/// \param flag true - ��������� ��� ���������� ������
	void setActivateByRelease(bool flag);

	/// ������������ ��� ���������� ������?
	/// \return true - ��������� ��� ���������� ������
	bool isActivatingByRelease() const;

	/// ����� �� �������� �� ������
	/// \param flag true - ������ ��������
	void setClickActive(bool flag);

	/// ����� �� �������� �� ������
	/// \return true - ������ �������
	bool isClickActive() const;

protected:
	/// ������ �� ������
	/// \return true - ������ ������
	bool isPressed() const;

	/// ����������� ������������ ������
	/// ����� ������ ���������� � ������-����������
	/// \param event �������� �������
	/// \param isMouseOver �������� �� ���� �� ������
	void tryActivate(const sf::Event& event, bool isMouseOver);

	/// �������, ������� �� ��������� ����� ���������� ��� ������� �� ������
	virtual void defaultClickAction() { }

private:
	Callback mCallback;

	bool mIsClickActive;
	bool mIsPressed;

	sf::Mouse::Button mActivationButton;
	bool mActivateByRelease;
};