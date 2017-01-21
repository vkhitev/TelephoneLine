/**
*
* \class Container
*
* \brief ������ �������� ����������������� ����������
*
* ������������� ���������, ������������ � ������������ �������� �������
* ��� ���� ��������� ������ ����������
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

#include <vector>
#include <map>
#include <memory>
#include <cassert>

namespace sf
{
	class RenderWindow;
	class Event;
	class Time;
}

namespace GUI
{

	class Container
	{
	public:
		typedef std::shared_ptr<Container> Ptr;


	public:
		/// ������� ���������
		/// \param window ���� ���������
		Container(sf::RenderWindow& window);

		/// �������� ������� � ���������
		/// \param key ���������� ���� (���) ��������
		/// \param component ����������� �������
		void pack(const std::string& key, Component::Ptr component);

		/// �������� ������� � ���������
		/// \param component ����������� �������
		void pack(Component::Ptr component);

		virtual void draw() const;
		virtual void update(sf::Time dt);
		virtual void handleEvent(const sf::Event& event);

		/// �������� ������� �� ����� � ����������� ����
		/// \param key ��� ��������
		template <typename DerivedType>
		std::shared_ptr<DerivedType> get(const std::string& key) const;

	protected:
		sf::RenderWindow& mWindow;

	private:
		std::map<std::string, Component::Ptr> mChildrenMap;
		std::vector<Component::Ptr> mChildrenArray;
	};


	template <typename DerivedType>
	std::shared_ptr<DerivedType> Container::get(const std::string& key) const
	{
		auto child = mChildrenMap.find(key);
		assert(child != cend(mChildrenMap) && "No value found in GUI::Container");
		assert(std::dynamic_pointer_cast<DerivedType>(child->second) != nullptr && "Bad downcast in GUI::Container");
		return std::static_pointer_cast<DerivedType>(child->second);
	}
}