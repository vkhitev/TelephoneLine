/**
*
* \class Timer
*
* \brief Считает время.
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
#include <chrono>
#include <ostream>

class Timer
{
public:
	Timer();

	/// Сбросить отсчёт
	void reset();

	/// Пройденное время в миллисекундах
	std::chrono::milliseconds elapsedMS() const;

	/// Пройденное время в секундах
	std::chrono::seconds elapsedS() const;

	/// Пройденное время в минутах
	std::chrono::minutes elapsedM() const;

	/// Выводит в поток время в миллисекундах
	friend std::ostream& operator<<(std::ostream& out, const Timer& timer);
private:
	/// Точка начала отсчёта
	std::chrono::high_resolution_clock::time_point mStart;
};