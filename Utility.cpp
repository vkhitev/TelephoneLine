#include "Utility.h"

#include <ctime>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <thread>
#include <mutex>

#include <SFML/Graphics/Shape.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

std::string getCurrentTime()
{
	std::ostringstream stream;
	std::time_t time = std::time(nullptr);
	tm* lt = std::localtime(&time);
	stream << std::put_time(lt, "%d") << "." << std::put_time(lt, "%m") << "." << std::put_time(lt, "%Y") << " " << std::put_time(lt, "%X");
	return stream.str();
}

std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems)
{
	std::stringstream ss(s);
	std::string item;
	while (std::getline(ss, item, delim))
	{
		elems.push_back(item);
	}
	return elems;
}


std::vector<std::string> split(const std::string &s, char delim)
{
	std::vector<std::string> elems;
	split(s, delim, elems);
	return elems;
}

void locked_cout(const std::string& message, std::mutex& mutex)
{
	mutex.lock();
	std::cout << message;
	mutex.unlock();
}

void pause()
{
	std::this_thread::sleep_for(std::chrono::nanoseconds(1));
	std::cout << "Press any key to continue...";
	std::cin.get();
}

void centerOrigin(sf::Sprite& sprite)
{
	sf::FloatRect bounds = sprite.getLocalBounds();
	sprite.setOrigin(std::floor(bounds.left + bounds.width / 2.f), std::floor(bounds.top + bounds.height / 2.f));
}

void centerOrigin(sf::Text& text)
{
	sf::FloatRect bounds = text.getLocalBounds();
	text.setOrigin(std::floor(bounds.left + bounds.width / 2.f), std::floor(bounds.top + bounds.height / 2.f));
}

void centerOrigin(sf::Shape& shape)
{
	sf::FloatRect bounds = shape.getLocalBounds();
	shape.setOrigin(std::floor(bounds.left + bounds.width / 2.f), std::floor(bounds.top + bounds.height / 2.f));
}

float length(sf::Vector2f vector)
{
	return std::sqrt(vector.x * vector.x + vector.y * vector.y);
}