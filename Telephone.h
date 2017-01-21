/**
*
* \class Telephone
*
* \brief Благодаря телефону пользователь может совершать, принимать звонки
* и делать другие крутые штуки.
*
* Позволяет набирать номер (как целиком, так и посимвольно), сбрасывать номер просматривать список контактов,
* историю вызовов.
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

#include "TelephoneDB.h"
#include "Timer.h"

#include "StateStack.h"
#include "AppContext.h"

#include <string>
#include <memory>
#include <atomic>

#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>

class SwitchingCenter;
class TelephoneLine;

class Telephone
{
public:
	/// \param nativeNumber Номер данного телефона
	/// \param switchingCenter Станция, с которой связан телефон
	Telephone(AppContext context, const std::string& nativeNumber, TelephoneLine& line);

	/// Установить номер, который набрал пользователь
	/// \param number Номер, набранный пользователем
	void setDialedNumber(const std::string& number);

	/// Установить номер данного телефона
	/// \param number Номер данного телефона
	void setNativeNumber(const std::string& number);

	/// Получить номер, который набрал пользователь
	const std::string& getDialedNumber() const;

	/// Получить номер данного телефона
	const std::string& getNativeNumber() const;

	/// Получить базу данных телефона
	const TelephoneDB& getDataBase() const;

	/// Добавить контакт в список контактов
	void addContact(const std::string& firstName, const std::string& lastName, const std::string& number);

	/// Добавить контакт в список контактов
	void addContact(const Contact& contact);

	/// Исключить контакт из базы контактов
	void removeContact(const std::string& firstName, const std::string& lastName);

	/// Исключить контакт из базы контактов
	void removeContact(const Contact& contact);
	
	/// Отправить сообщение text на номер number
	void sendMessage(const std::string& number, const std::string& text);

	/// Совершить звонок на номер mDialedNumber
	void call();

	/// Принять входящий вызов
	void accept();

	/// Сбросить входящий вызов
	void decline();

	/// Присоедениться к вызову
	void connect();

	/// Отсоединиться (сбросить текущий вызов)
	void disconnect();

	/// Есть ли связь между телефонами
	bool isConnected() const;

	/// Занят ли телефон
	bool isBusy() const;

	/// Есть ли входящий звонок
	bool isGettingCall() const;

	/// Получить входящий звонок
	void getCall(const std::string& caller);

	/// Получить сообщение
	void getMessage(const std::string& sender, const std::string& text);

	/// Получить имя звонящего
	std::string getCaller() const;

	/// Идёт ли вызов другого телефона
	void setCalling(bool flag);

	/// Идёт ли исходящий звонок
	bool isCalling() const;

	/// Находится ли телефон в зоне доступа (привязан ли к станции)
	bool isInConnectionZone() const;

	/// Привязать телефон к станции
	void setSwicthingCenter(const std::shared_ptr<SwitchingCenter>& center);
	void connectToNearestSwitchingCenter();

	void handleEvent(const sf::Event& event);
	void update(sf::Time dt);
	void draw() const;

	void setPosition(const sf::Vector2f& position);
	void setSize(const sf::Vector2f& size);

	sf::Vector2f getPosition() const;
	sf::Vector2f getSize() const;

	void setStateParam(const std::string& param);
	std::string getStateParam() const;

private:
	void registerStates();

private:
	TelephoneLine&					mTelephoneLine; ///< Телефонная линия, породившая телефон
	std::weak_ptr<SwitchingCenter>	mSwitchingCenter; ///< АТС, с которой связан телефон
	TelephoneDB						mDataBase; ///< База данных (контакты и история звонков)
	std::string						mNativeNumber; ///< Номер данного телефона
	std::string						mDialedNumber; ///< Текущий набранный номер

	std::atomic<bool>				mIsCalling; ///< Идёт ли вызов другого телефона
	std::atomic<bool>				mIsConnected; ///< Установлена ли связь между телефонами
	std::atomic<bool>				mIsGettingCall; ///< Есть ли входящий вызов

	Timer							mTimer; ///< Таймер для отсчёта длительности звонка
	std::string						mCaller; ///< Номер телефона, с которого поступил вызов

	StateStack						mStateStack; ///< Стек состояний (слоёв) всех меню телефона
	sf::Vector2f					mPosition; ///< Позиция телефона на экране
	sf::Vector2f					mSize; ///< Размер телефона
	std::string						mStateParam; ///< Переменная для передачи между состояниями
};