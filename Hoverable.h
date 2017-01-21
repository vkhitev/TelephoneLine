/**
*
* \class Hoverable
*
* \brief �� ������� ������� ����������� ����� �������� ����� - ����� ������� ������������ �������.
*
* ������� ��������������� ������ "bool isMouseOver() const"
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

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class Hoverable
{
public:
	Hoverable(sf::RenderWindow& window);
	virtual ~Hoverable() = default;

	/// ���������� ���������� ��� ��������� �����
	/// \param flag true - ��������� �������
	void setHoverActive(bool flag);

	/// ������� �� ������ ��� ���������
	/// \param flag true - ��������� �������
	bool isHoverActive() const;

protected:
	bool isMouseOver(const sf::FloatRect& bounds) const;
	virtual void defaultHoverAction() { }

private:
	virtual bool isMouseOver() const = 0;

	sf::RenderWindow& mWindow;
	bool mIsHoverActive;
};