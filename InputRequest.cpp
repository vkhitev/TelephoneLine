#include "InputRequest.h"

namespace GUI
{
	InputRequest::InputRequest(AppContext context, const std::string& request)
		: Container(context.getWindow())
		, mBorder({ 300, 200 })
	{
		auto leftButton = std::make_shared<Button>(context);
		auto rightButton = std::make_shared<Button>(context);
		auto label = std::make_shared<Label>(context.getFonts().get(Fonts::Main), request);

		mBorder.setFillColor({ 50, 50, 50, 50 });
		mBorder.setOutlineColor(sf::Color::Black);
		mBorder.setOutlineThickness(1.f);

		pack("left", leftButton);
		pack("right", rightButton);
		pack("label", label);
	}

	void InputRequest::setPosition(const sf::Vector2f& position)
	{
		mBorder.setPosition(position);
		auto midPoint = position + mBorder.getSize() / 2.f;

		auto leftButton = get<Button>("left");
		auto rightButton = get<Button>("left");
		auto label = get<Label>("left");

		leftButton->setPosition(midPoint + sf::Vector2f(100, 50));
		rightButton->setPosition(midPoint + sf::Vector2f(-100, 50));
		label->setPosition(midPoint - sf::Vector2f(0, 50));
	}

	void InputRequest::setSize(const sf::Vector2f& size)
	{
		mBorder.setSize(size);
		auto midPoint = mBorder.getPosition() + size / 2.f;

		auto leftButton = get<Button>("left");
		auto rightButton = get<Button>("left");
		auto label = get<Label>("left");

		leftButton->setPosition(midPoint + sf::Vector2f(100, 50));
		rightButton->setPosition(midPoint + sf::Vector2f(-100, 50));
		label->setPosition(midPoint - sf::Vector2f(0, 50));
	}

	void InputRequest::draw() const
	{
		mWindow.draw(mBorder);
		Container::draw();
	}

	//void InputRequest::update(sf::Time dt)
	//{

	//}

	//void InputRequest::handleEvent(const sf::Event& event)
	//{

	//}
}