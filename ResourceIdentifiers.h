#pragma once

namespace sf
{
	class Texture;
	class Font;
}

namespace Textures
{
	/// Идентификаторы текстур
	enum ID
	{
		Background,
		Telephone,
		SwitchingCenter,
		Button
	};
}

namespace Fonts
{
	// Идентификаторы шрифтов
	enum ID
	{
		Main,
	};
}

// Предварительное объявление класса
template <typename Resource, typename Identifier>
class ResourceHolder;

typedef ResourceHolder<sf::Texture, Textures::ID> TextureHolder;
typedef ResourceHolder<sf::Font, Fonts::ID>	FontHolder;