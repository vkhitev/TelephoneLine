#include "Container.h"

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Time.hpp>

namespace GUI
{

	Container::Container(sf::RenderWindow& window)
		: mWindow(window)
		, mChildrenMap()
		, mChildrenArray()
	{
	}

	void Container::pack(const std::string& key, Component::Ptr component)
	{
		mChildrenMap.insert(std::make_pair(key, component));
	}

	void Container::pack(Component::Ptr component)
	{
		mChildrenArray.push_back(component);
	}

	void Container::draw() const
	{
		for (const auto& child : mChildrenArray)
			mWindow.draw(*child);
		for (const auto& child : mChildrenMap)
			mWindow.draw(*child.second);
	}

	void Container::update(sf::Time dt)
	{
		for (auto& child : mChildrenArray)
			child->update(dt);
		for (auto& child : mChildrenMap)
			child.second->update(dt);
	}

	void Container::handleEvent(const sf::Event& event)
	{
		for (auto& child : mChildrenArray)
			child->handleEvent(event);
		for (auto& child : mChildrenMap)
			child.second->handleEvent(event);
	}
}