#pragma once

#include <string>
#include <vector>
#include <iostream>

#include <SFML/System/Vector2.hpp>

/// Получить текущее время в формате dd.mm.yyyy hh:mm:ss
std::string getCurrentTime();

std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems);
std::vector<std::string> split(const std::string &s, char delim);

template <typename T>
T request(const std::string& what)
{
	T answer;
	std::cout << what + ":\n>> ";
	std::cin >> answer;
	std::cout << std::endl;
	return answer;
}

template<>
inline std::string request<std::string>(const std::string& what)
{
	std::string answer;
	std::cout << what + ":\n>> ";
	fflush(stdin);
	std::getline(std::cin, answer, '\n');
	std::cout << std::endl;
	return answer;
}

namespace std
{
	class mutex;
}

void locked_cout(const std::string& message, std::mutex& mutex);

void pause();

namespace sf
{
	class Sprite;
	class Text;
	class Shape;
}

void centerOrigin(sf::Sprite& sprite);
void centerOrigin(sf::Text& text);
void centerOrigin(sf::Shape& shape);

float length(sf::Vector2f vector);