/**
*
* \class Button
*
* \brief Прямоугольная кнопка.
*
* При нажатии на кнопку вызывается заданная пользователем функция.
* Можно задавать цвет, шрифт, положение, размеры, состояние активности и пр.
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
		/// Создаёт кнопку
		/// \param context Графический контекст приложения
		Button(AppContext context);

		/// Установить текст кнопки
		/// \param text Текст кнопки
		void setText(const std::string& text);

		/// Установить размер текста кнопки
		/// \param size Размер текста кнопки
		void setTextSize(const unsigned int size);

		/// Установить размер кнопки
		/// \param size Размер кнопки
		void setSize(const sf::Vector2f& size);

		/// Установить размер кнопки
		/// \param x Ширина кнопки
		/// \param y Длина кнопки
		void setSize(float x, float y);

		/// Установить тип шрифта
		/// \param font Тип шрифта
		void setFont(sf::Font& font);

		/// Установить ширину рамки
		/// \param thickness Ширина рамки
		void setOutlineThickness(float thickness);


		/// Установить цвет заливки обычной кнопки
		/// \param color Цвет заливки обычной кнопки
		void setBackgroundColor(const sf::Color& color);

		/// Установить цвет текста обычной кнопки
		/// \param color Цвет текста обычной кнопки
		void setTextColor(const sf::Color& color);

		/// Установить цвет рамки обычной кнопки
		/// \param color Цвет рамки обычной кнопки
		void setOutlineColor(const sf::Color& color);


		/// Установить цвет заливки кнопки, на которую наведена мышь
		/// \param color Цвет заливки кнопки, на которую наведена мышь
		void setOverBackgroundColor(const sf::Color& color);

		/// Установить цвет текста кнопки, на которую наведена мышь
		/// \param color Цвет текста кнопки, на которую наведена мышь
		void setOverTextColor(const sf::Color& color);

		/// Установить цвет рамки кнопки, на которую наведена мышь
		/// \param color Цвет рамки кнопки, на которую наведена мышь
		void setOverOutlineColor(const sf::Color& color);


		/// Установить цвет заливки неактивной кнопки
		/// \param color Цвет заливки неактивной кнопки
		void setUnactiveBackgroundColor(const sf::Color& color);

		/// Установить цвет текста неактивной кнопки
		/// \param color Цвет текста неактивной кнопки
		void setUnactiveTextColor(const sf::Color& color);

		/// Установить цвет рамки неактивной кнопки
		/// \param color Цвет рамки неактивной кнопки
		void setUnactiveOutlineColor(const sf::Color& color);

		/// Получить текст кнопки
		/// \return Текст кнопки
		std::string getText() const;

		/// Обновить кнопку
		virtual void update(sf::Time dt) override;

		// Обработать входящее событие
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