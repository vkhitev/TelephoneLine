/**
*
* \class SwitchingCenter
*
* \brief Телефонная станция (АТС) устанавливает связь между двумя (пока что двумя) телефонами.
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

#include "Telephone.h"
#include "RegisteredCall.h"
#include "Message.h"

#include <string>
#include <memory>
#include <map>
#include <vector>

class SwitchingCenter
{
public:
	/// Состояние ошибки при вызове. None - нет ошибки
	enum ErrorState
	{
		None,
		Unregistered,
		Busy,
		WrongNumber,
		OutOfZone,
	};

public:
	/// Создаёт АТС
	SwitchingCenter(AppContext context);

	/// Заносит телефон в базу данных
	void registerTelephone(const std::shared_ptr<Telephone>& telephone);

	/// Находится ли номер в базе
	bool isRegistered(const std::string& number);

	/// Попробовать установить связь между вызывающим и вызывающимся телефонами
	void connect(Telephone& caller, const std::string& number);

	/// Отправляет сообщение text от отправителя sender на номер number
	bool sendMessage(Telephone& sender, const std::string& number, const std::string& text);

	std::vector<RegisteredCall> getLateCalls(const std::string& number);
	std::vector<Message> getLateMessages(const std::string& number);

private:
	/// Проверка номера на правильность (TODO)
	bool isNumberValid(const std::string& number) const;

	/// Получить состояние ошибки звонка, если она имеется
	ErrorState getCallErrorState(const std::string& number);

	/// Получить состояние ошибки отправки сообщения, если она имеется
	ErrorState getMessageErrorState(const std::string& number);

	void printError(ErrorState error);

private:
	/// Ассоц. массив "номер телефона : телефон" - зарегестрированные в базе телефоны
	std::map<std::string, std::weak_ptr<Telephone>> mRegisteredTelephones;

	std::map<std::string, std::vector<RegisteredCall>> mLateCalls; ///< Недошедшие звонки
	std::map<std::string, std::vector<Message>> mLateMessages; ///< Недошедшие сообщения

	const static int sMaxNumberDigits; ///< Максимальное количество цифер в номере
};