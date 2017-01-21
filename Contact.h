/**
*
* \class Contact
*
* \brief Содержит полную информацию о телефонном контакте
*
* Содержит имя, фамилию и номер контакта. Позволяет изменять и получать эти атрибуты.
* В будущем, возможно, будут добавлены атрибуты "почтовый адрес", "альтернативный номер" и др.
*
* \author Хитёв Владислав
*
* \version 8.0
*
* \date 2015/12/23
*
* Contact: vkhitev@gmail.com
*
*/

#pragma once

#include <string>

class Contact
{
public:
	/// Создать пустой контакт
	Contact();

	/// Создать контакт
	/// \param firstName Имя контакта
	/// \param lastName Фамилия контакта
	/// \param number Номер телефона
	Contact(const std::string& firstName, const std::string& lastName, const std::string& number);

	/// Установить имя контакта
	void setFirstName(const std::string& firstName);

	/// Установить фамилию контакта
	void setLastName(const std::string& lastName);

	/// Установить номер телефона
	void setNumber(const std::string& number);

	/// \return Имя контакта
	const std::string& getFirstName() const;

	/// \return Фамилия контакта
	const std::string& getLastName() const;

	/// \return Номер телефона
	const std::string& getNumber() const;

	/// \return Имя и фамилия
	std::string getFullName() const;

	/// Сравнение по имени и фамилии
	friend bool operator<(const Contact& a, const Contact& b);

private:

	std::string		mFirstName; ///< Имя контакта
	std::string		mLastName; ///< Фамилия контакта
	std::string		mNumber; ///< Телефонный номер контакта
};