/**
*
* \class Button
*
* \brief ������������� ������.
*
* ��� ������� �� ������ ���������� �������� ������������� �������.
* ����� �������� ����, �����, ���������, �������, ��������� ���������� � ��.
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

#include "AppContext.h"
#include "Component.h"
#include "Clickable.h"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>

#include <string>
#include <memory>

namespace GUI
{

	class Button : public GUI::Component, public Clickable
	{
	public:
		typedef std::shared_ptr<Button> Ptr;

	public:
		/// ������ ������
		/// \param context ����������� �������� ����������
		Button(AppContext context);

		/// ���������� ����� ������
		/// \param text ����� ������
		void setText(const std::string& text);

		/// ���������� ������ ������ ������
		/// \param size ������ ������ ������
		void setTextSize(const unsigned int size);

		/// ���������� ������ ������
		/// \param size ������ ������
		void setSize(const sf::Vector2f& size);

		/// ���������� ������ ������
		/// \param x ������ ������
		/// \param y ����� ������
		void setSize(float x, float y);

		/// ���������� ��� ������
		/// \param font ��� ������
		void setFont(sf::Font& font);

		/// ���������� ������ �����
		/// \param thickness ������ �����
		void setOutlineThickness(float thickness);


		/// ���������� ���� ������� ������� ������
		/// \param color ���� ������� ������� ������
		void setBackgroundColor(const sf::Color& color);

		/// ���������� ���� ������ ������� ������
		/// \param color ���� ������ ������� ������
		void setTextColor(const sf::Color& color);

		/// ���������� ���� ����� ������� ������
		/// \param color ���� ����� ������� ������
		void setOutlineColor(const sf::Color& color);


		/// ���������� ���� ������� ������, �� ������� �������� ����
		/// \param color ���� ������� ������, �� ������� �������� ����
		void setOverBackgroundColor(const sf::Color& color);

		/// ���������� ���� ������ ������, �� ������� �������� ����
		/// \param color ���� ������ ������, �� ������� �������� ����
		void setOverTextColor(const sf::Color& color);

		/// ���������� ���� ����� ������, �� ������� �������� ����
		/// \param color ���� ����� ������, �� ������� �������� ����
		void setOverOutlineColor(const sf::Color& color);


		/// ���������� ���� ������� ���������� ������
		/// \param color ���� ������� ���������� ������
		void setUnactiveBackgroundColor(const sf::Color& color);

		/// ���������� ���� ������ ���������� ������
		/// \param color ���� ������ ���������� ������
		void setUnactiveTextColor(const sf::Color& color);

		/// ���������� ���� ����� ���������� ������
		/// \param color ���� ����� ���������� ������
		void setUnactiveOutlineColor(const sf::Color& color);

		/// �������� ����� ������
		/// \return ����� ������
		std::string getText() const;

		/// �������� ������
		virtual void update(sf::Time dt) override;

		// ���������� �������� �������
		virtual void handleEvent(const sf::Event& event) override;

	private:
		void updateTextPosition();
		virtual bool isMouseOver() const override;
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	private:
		sf::RectangleShape mShape;
		sf::Text mText;		

		sf::Color mBackgroundColor;
		sf::Color mTextColor;
		sf::Color mOutlineColor;

		sf::Color mOverBackgroundColor;
		sf::Color mOverTextColor;
		sf::Color mOverOutlineColor;

		sf::Color mUnactiveBackgroundColor;
		sf::Color mUnactiveOverTextColor;
		sf::Color mUnactiveOverOutlineColor;
	};

}