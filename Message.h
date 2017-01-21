/**
*
* \class Message
*
* \brief Содержит информацию об СМС-сообщении
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

class Message
{
public:
	enum State    ///< Тип сообщения
	{
		Imcoming, ///< Входящее
		Outgoing, ///< Исходящее
	};

public:
	/// Создать звонок
	/// \param state Тип звонка (входящий/исходящий/пропущенный)
	/// \param caller Номер звонящего
	/// \param time Время начала звонка
	/// \param duration Длительность звонка
	Message(State state, const std::string& sender, const std::string& time, const std::string& text);

	/// \return Тип звонка
	State getState() const;

	/// \return Номер звонящего
	const std::string& getSender() const;

	/// \return Время начала звонка
	const std::string& getTime() const;

	/// \return Текст сообщения
	const std::string& getText() const;

	/// Установить тип звонка
	void setState(State state);

	/// Установить номер звонящего
	void setSender(const std::string& sender);

	/// Установить время начала звонка
	/// Формат - dd.mm.yyyy hh:mm:ss
	void setTime(const std::string& time);

	/// Установить текст сообщения
	void setText(const std::string& text);

private:
	/// Проверка времени на валидность
	bool isTimeValid(const std::string& time) const;

	State			mState; ///< Тип (входящее или исходящее сообщение)
	std::string		mSender; ///< Полное имя контакта, который звонил (которому звонили)
	std::string		mCallTime; ///< Время, в которое пришло или ушло сообщение
	std::string		mText; ///< Текст сообщения
};