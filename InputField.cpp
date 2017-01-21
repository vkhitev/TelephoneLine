#include "InputField.h"

#include "Utility.h"

namespace GUI
{
	InputField::InputField(const sf::Vector2f& position, const sf::Vector2f& size,
		const sf::Font& font, unsigned int characterSize, const sf::String& tip)
		: mTip(tip)
		, mString()
		, mText(tip, font, characterSize)
		, mShape(size)
		, mCursor(sf::Vector2f(2.f, characterSize * 1.3f))
		, mIsTipInField(true)
		, mIsCharAdded(false)
		, mSubmitAction()
	{
		float xOffset = 5.f;
		float yOffset = (size.y - characterSize * 1.3f) / 2;
		sf::Vector2f offset(xOffset, yOffset);

		onFocusGain([this]()
		{
			if (mIsTipInField)
			{
				mText.setString("");
				mText.setColor(sf::Color::Black);
				mIsTipInField = false;
			}
			adaptCursorPosition();
		});

		onFocusLoose([this]()
		{
			if (mText.getString().isEmpty())
			{
				mText.setString(mTip);
				mText.setColor({ 100, 100, 100 });
				mIsTipInField = true;
			}
			mCursor.setFillColor(sf::Color::White);
		});

		mShape.setOutlineThickness(3.f);
		mShape.setOutlineColor(sf::Color::Black);

		mText.setPosition(offset);
		mText.setColor({ 100, 100, 100 });

		mCursor.setFillColor(sf::Color::White);

		setPosition(position);
	}

	void InputField::handleEvent(sf::RenderWindow& window, const sf::Event& event)
	{
		Interactive::handleEvent(window, event);

		if (isFocused())
		{
			if (event.type == sf::Event::TextEntered)
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Return))
				{
					if (mSubmitAction)
						mSubmitAction();
				}

				else if (event.text.unicode < 128 && !sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace))
				{
					addChar(static_cast<char>(event.text.unicode));
					adaptCursorPosition();
					mIsCharAdded = true;
				}
			}
		}
	}

	void InputField::updateHover(sf::RenderWindow& window, sf::Time dt)
	{
		static sf::Time elapsedErase = sf::Time::Zero;
		static sf::Time elapsedCursor = sf::Time::Zero;
		static bool firstErase = true;

		if (isFocused())
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace))
			{
				if (firstErase)
				{
					removeChar();
					adaptCursorPosition();
					firstErase = false;
					elapsedErase = sf::milliseconds(-420);
				}

				elapsedErase += dt;
				if (elapsedErase > sf::milliseconds(30))
				{
					removeChar();
					adaptCursorPosition();
					elapsedErase = sf::Time::Zero;
				}
			}
			else
			{
				elapsedErase = sf::Time::Zero;
				firstErase = true;
			}

			elapsedCursor += dt;
			if (mIsCharAdded)
			{
				mIsCharAdded = false;
				elapsedCursor = sf::Time::Zero;
			}

			if (elapsedCursor > sf::milliseconds(500))
			{
				if (mCursor.getFillColor() == sf::Color::Black)
					mCursor.setFillColor(sf::Color::White);
				else
					mCursor.setFillColor(sf::Color::Black);
				elapsedCursor = sf::Time::Zero;
			}
		}
	}

	const sf::String& InputField::getString() const
	{
		return mString;
	}

	void InputField::onSubmit(Callback callback)
	{
		mSubmitAction = std::move(callback);
	}

	void InputField::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(mShape, states);
		target.draw(mCursor, states);
		target.draw(mText, states);
	}

	sf::FloatRect InputField::getBoundingRect() const
	{
		auto rect = static_cast<sf::FloatRect>(mShape.getGlobalBounds());
		auto pos = getWorldPosition();
		rect.left += pos.x;
		rect.top += pos.y;
		return rect;
	}

	bool InputField::isMouseOver(sf::RenderWindow& window) const
	{
		return Interactive::isMouseOver(getBoundingRect(), window);
	}

	void InputField::adaptText()
	{
		unsigned int chSize = mText.getCharacterSize();
		while (mText.getGlobalBounds().width > mShape.getSize().x - chSize)
		{
			sf::String str = mText.getString();
			str = str.substring(1, str.getSize());
			mText.setString(str);
		}
	}

	void InputField::adaptCursorPosition()
	{
		auto bounds = mText.getGlobalBounds();
		auto xPos = bounds.left + bounds.width + 1;
		auto yPos = (mShape.getSize().y - mText.getCharacterSize() * 1.3f) / 2;

		mCursor.setPosition(xPos, yPos);


		mCursor.setFillColor(sf::Color::Black);
	}

	void InputField::addChar(char ch)
	{
		mString += ch;
		mText.setString(mText.getString() + ch);
		adaptText();
	}

	void InputField::removeChar()
	{
		mString = mString.substring(0, mString.getSize() - 1);
		auto stringToPut = mString;
		auto size = mText.getString().getSize();
		if (mString.getSize() > size)
			stringToPut = mString.substring(mString.getSize() - size);
		mText.setString(stringToPut);
	}
}