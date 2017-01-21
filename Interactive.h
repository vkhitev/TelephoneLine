#pragma once

#include <functional>
#include <map>

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

namespace sf
{
	class RenderWindow;
	class Event;
}

namespace GUI
{
	class Interactive
	{
	public:
		using Callback = std::function<void()>;

	public:
		Interactive();
		virtual ~Interactive() = default;

		void onHover(Callback callback);
		void onFocusGain(Callback callback);
		void onFocusLoose(Callback callback);
		void onMouseEnter(Callback callback);
		void onMouseLeave(Callback callback);
		void onLeftClick(Callback callback);
		void onRightClick(Callback callback);
		void onMiddleClick(Callback callback);

		void setFocused(bool focused);
		bool isFocused() const;

		void setActive(bool active);
		bool isActive() const;

		virtual void handleEvent(sf::RenderWindow& window, const sf::Event& event);
		virtual void updateHover(sf::RenderWindow& window, sf::Time dt);

	protected:
		bool isMouseOver(const sf::FloatRect& bounds, sf::RenderWindow& window) const;
		bool isMouseOver(const sf::IntRect& bounds, sf::RenderWindow& window) const;
		virtual bool isMouseOver(sf::RenderWindow& window) const = 0;

	private:
		enum Action { Hover, FocusGain, FocusLoose, MouseEnter, MouseLeave, Left, Right, Middle };

		struct CallbackStruct
		{
			CallbackStruct();
			Callback callback;
			bool isPressed;
			sf::Mouse::Button triggerButton;
		};

	private:
		std::map<Action, CallbackStruct> mActions;
		bool mIsFocused;
		bool mIsMouseEntered;
		bool mIsActive;
	};
}