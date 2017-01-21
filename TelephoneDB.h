/**
*
* \class TelephoneDB
*
* \brief База данных телефона, которая содержит контакты и историю вызовов.
*
* Позволяет получить список контактов и историю вызовов, а также автоматически
* добавлять в нужном порядке новые элементы.
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

#include "Contact.h"
#include "RegisteredCall.h"
#include "Message.h"

#include <set>
#include <deque>

class TelephoneDB
{
public:
	/// Создаёт БД телефона
	TelephoneDB();

	/// Зарегестрировать вызов
	/// \param state Тип звонка (входящий/исходящий/пропущенный)
	/// \param caller Номер звонящего
	/// \param time Время начала звонка
	/// \param duration Длительность звонка
	void registerCall(RegisteredCall::State state, const std::string& caller, const std::string& time, unsigned int duration);

	void registerCallWithNumber(const RegisteredCall& call);

	/// Зарегестрировать сообщение
	/// \param state Тип сообщения (входящее/исходящее)
	/// \param sender Номер отправителя
	/// \param time Время отправки
	/// \param text Текст сообщения
	void registerMessage(Message::State state, const std::string& sender, const std::string& time, const std::string& text);

	void registerMessageWithNumber(const Message& message);

	/// Добавить контакт в список контактов
	void addContact(const std::string& firstName, const std::string& lastName, const std::string& number);

	/// Добавить контакт в список контактов
	void addContact(const Contact& contact);

	/// Исключить контакт из базы контактов
	void removeContact(const std::string& firstName, const std::string& lastName);

	/// Исключить контакт из базы контактов
	void removeContact(const Contact& contact);

	/// \return Список контактов
	const std::set<Contact> getContacts() const;

	/// \return Список совершенных звонков
	const std::deque<RegisteredCall> getCalls() const;

	/// \return Список сообщений
	const std::deque<Message> getMessages() const;

	/// Находит имя по номеру в списке контактов
	std::string findName(const std::string& number) const;

private:
	/// Заменяет номера на имена (в списке звонков и сообщениях), если контакт был добавлен в базу
	void replaceNumberInCallsAndMessages(const Contact& contact);

	/// Заменяет имена на номера (в списке звонков и сообщениях), если контакт был удалён из базы
	void replaceCallerInCallsAndMessages(const Contact& contact);

	std::set<Contact>			mContacts; ///< Список контактов
	std::deque<RegisteredCall>	mRegisteredCalls; ///< Список звонков: входящих, исходящих, пропущенных
	std::deque<Message>			mMessages; ///< Список сообщений: входящих, исходящих
};