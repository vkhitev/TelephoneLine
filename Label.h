/**
*
* \class Label
*
* \brief �������
*
* ����� �������� ���������, ������ � ���� ������, ��� ������
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

#include "Component.h"

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>

namespace GUI
{

	class Label : public GUI::Component
	{
	public:
		/// ������ �������
		/// \param font ��� ������
		/// \param text ���������� �����
		/// \param size ������ ������
		/// \param centralized ������� �� origin � ������� �������
		Label(sf::Font& font, const std::string& text, const unsigned int size = 30U,
			bool centralized = true);

		/// ���������� ����� �������
		/// \param text ����� �������
		void setText(const sf::Text& text);

		/// �������� ����� �������
		/// \return ����� �������
		const sf::Text& getText() const;

		/// ���������� ����� �������
		/// \param string ����� �������
		void setString(const std::string& string);

		/// �������� ����� �������
		/// \return ����� �������
		std::string getString() const;

		/// ���������� ������ ������
		/// \param size ������ ������
		void setCharacterSize(const unsigned int size);

		/// ���������� ���� ������
		/// \param color ���� ������
		void setColor(const sf::Color& color);

		/// ������� origin � ������� �������
		void setCenterOrigin();

		/// ������� origin � ����� ������� ����� �������
		void setDefaultOrigin();

		/// �������� �������
		virtual void update(sf::Time dt) override;

		/// ���������� �������� �������
		virtual void handleEvent(const sf::Event& event) override;

	private:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

		void applyOrigin();

		sf::Text	 mText;
		bool		 mIsOriginCentralized;
	};
}
