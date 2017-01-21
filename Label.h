/**
*
* \class Label
*
* \brief Надпись
*
* Можно изменять положение, размер и цвет текста, тип шрифта
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

#include "Component.h"

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>

namespace GUI
{

	class Label : public GUI::Component
	{
	public:
		/// Создаёт надпись
		/// \param font Тип шрифта
		/// \param text Собственно текст
		/// \param size Размер шрифта
		/// \param centralized Связать ли origin с центром надписи
		Label(sf::Font& font, const std::string& text, const unsigned int size = 30U,
			bool centralized = true);

		/// Установить текст надписи
		/// \param text Текст надписи
		void setText(const sf::Text& text);

		/// Получить текст надписи
		/// \return Текст надписи
		const sf::Text& getText() const;

		/// Установить текст надписи
		/// \param string Текст надписи
		void setString(const std::string& string);

		/// Получить текст надписи
		/// \return Текст надписи
		std::string getString() const;

		/// Установить размер шрифта
		/// \param size Размер шрифта
		void setCharacterSize(const unsigned int size);

		/// Установить цвет шрифта
		/// \param color Цвет шрифта
		void setColor(const sf::Color& color);

		/// Связать origin с центром надписи
		void setCenterOrigin();

		/// Связать origin с левым верхним углом надписи
		void setDefaultOrigin();

		/// Обновить надпись
		virtual void update(sf::Time dt) override;

		/// Обработать входящее событие
		virtual void handleEvent(const sf::Event& event) override;

	private:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

		void applyOrigin();

		sf::Text	 mText;
		bool		 mIsOriginCentralized;
	};
}
