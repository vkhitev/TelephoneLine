#pragma once

namespace sf
{
	class Texture;
	class Font;
}

namespace Textures
{
	/// �������������� �������
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
	// �������������� �������
	enum ID
	{
		Main,
	};
}

// ��������������� ���������� ������
template <typename Resource, typename Identifier>
class ResourceHolder;

typedef ResourceHolder<sf::Texture, Textures::ID> TextureHolder;
typedef ResourceHolder<sf::Font, Fonts::ID>	FontHolder;