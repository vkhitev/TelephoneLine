/**
*
* \class ResourceHolder
*
* \brief Контейнер ресурсов.
*
* Содержит ресурс (текстуру, шрифт, звук) с уникальным ID.
* Есть возможность загрузить и получить ресурс по ID.
*
* \author SFML | Хитёв Владислав
*
* \copyright http://www.sfml-dev.org/
*
*/

#pragma once

#include <map>
#include <string>
#include <memory>
#include <stdexcept>
#include <cassert>

template <typename Resource, typename Identifier>
class ResourceHolder
{
public:
	using Ptr = std::unique_ptr < Resource >;

	/// Загрузить новый ресурс
	/// \param id Уникальный ключ ресурса
	/// \param filename Относительный путь к ресурсу
	void load(Identifier id, const std::string& filename);

	/// Загрузить новый ресурс
	/// \param id Уникальный ключ ресурса
	/// \param filename Относительный путь к ресурсу
	/// \param secondParam Дополнительный параметр (необходим для некоторых ресурсов)
	template <typename Parameter>
	void load(Identifier id, const std::string& filename, const Parameter& secondParam);

	/// Получить ресурс по ключу
	/// \param id Ключ ресурса
	/// \return Ссылка на ресурс
	Resource& get(Identifier id);

	/// Получить ресурс по ключу
	/// \param id Ключ ресурса
	/// \return Ссылка на ресурс
	const Resource&	get(Identifier id) const;

private:
	/// Добавть ресурс в массив
	/// \param id Ключ (идентификатор)
	/// \param resource Значение (ресурс)
	void insertResource(Identifier id, Ptr&& resource);

private:
	/// Массив ID - Ресурс, содержащий текстуры
	std::map<Identifier, Ptr> mResourceMap;
};

#include "ResourceHolder.inl"