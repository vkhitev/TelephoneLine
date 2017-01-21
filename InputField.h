#pragma once

#include "SceneNode.h"
#include "Interactive.h"

#include "SFML/System/String.hpp"
#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/Text.hpp"
#include "SFML/Graphics/RectangleShape.hpp"

namespace GUI
{
	class InputField : public SceneNode, public Interactive
	{
	public:
		InputField(const sf::Vector2f& position, const sf::Vector2f& size,
			const sf::Font& font, unsigned int characterSize, const sf::String& tip = "");

		virtual void handleEvent(sf::RenderWindow& window, const sf::Event& event) override;
		virtual void updateHover(sf::RenderWindow& window, sf::Time dt) override;

		const sf::String& getString() const;
		void onSubmit(Callback callback);

	private:
		virtual sf::FloatRect getBoundingRect() const override;
		virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;
		virtual bool isMouseOver(sf::RenderWindow& window) const override;

		void adaptText();
		void adaptCursorPosition();
		void addChar(char ch);
		void removeChar();

	private:
		sf::String mTip;
		sf::String mString;
		sf::Text mText;
		sf::RectangleShape mShape;
		sf::RectangleShape mCursor;
		bool mIsTipInField;
		bool mIsCharAdded;
		Callback mSubmitAction;
	};
}