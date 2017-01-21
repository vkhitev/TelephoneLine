#pragma once

#include "Container.h"
#include "Button.h"
#include "Label.h"

namespace GUI
{
	class InputRequest : public Container
	{
	public:
		InputRequest(AppContext context, const std::string& request);

		void setPosition(const sf::Vector2f& position);
		void setSize(const sf::Vector2f& size);

		virtual void draw() const;
		/*virtual void update(sf::Time dt);
		virtual void handleEvent(const sf::Event& event);*/
	private:
		sf::RectangleShape mBorder;
	};
}