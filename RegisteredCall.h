/**
*
* \class RegisteredCall
*
* \brief Содержит информацию о случившемся звонке (входящем или исходящем)
*
* Фиксирует тип звонка, имя звонящего (звонившего), время и длительность разговора.
* Позволяет получить перечисленные атрибуты атрибуты.
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

class RegisteredCall
{
public:
	enum State    ///< Перечисление типов вызовов
	{
		Imcoming, ///< Входящий вызов
		Outgoing, ///< Исходящий вызов
		Missed,   ///< Пропущенный вызов
	};

public:
	/// Создать звонок
	/// \param state Тип звонка (входящий/исходящий/пропущенный)
	/// \param caller Номер звонящего
	/// \param time Время начала звонка
	/// \param duration Длительность звонка
	RegisteredCall(State state, const std::string& caller, const std::string& time, unsigned int duration);

	/// \return Тип звонка
	State getState() const;

	/// \return Тип звонка как строка
	std::string getStrState() const;

	/// \return Номер звонящего
	const std::string& getCaller() const;

	/// \return Время начала звонка
	const std::string& getTime() const;

	/// \return Длительность звонка
	unsigned int getDuration() const;

	/// Установить тип звонка
	void setState(State state);

	/// Установить номер звонящего
	void setCaller(const std::string& caller);

	/// Установить время начала звонка
	/// Формат - dd.mm.yyyy hh:mm:ss
	void setTime(const std::string& time);

	/// Установить длительность звнка
	void setDuration(unsigned int duration);

private:
	/// Проверка времени на валидность
	bool isTimeValid(const std::string& time) const;

	State			mState; ///< Тип вызова
	std::string		mCaller; ///< Полное имя контакта, который звонил (которому звонили)
	std::string		mCallTime; ///< Время, в которое установилось соединение
	unsigned int	mCallDuration; ///< Длительность звонка
};