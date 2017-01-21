/**
*
* \class Telephone
*
* \brief ��������� �������� ������������ ����� ���������, ��������� ������
* � ������ ������ ������ �����.
*
* ��������� �������� ����� (��� �������, ��� � �����������), ���������� ����� ������������� ������ ���������,
* ������� �������.
*
* \author ���� ���������
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
	/// \param nativeNumber ����� ������� ��������
	/// \param switchingCenter �������, � ������� ������ �������
	Telephone(AppContext context, const std::string& nativeNumber, TelephoneLine& line);

	/// ���������� �����, ������� ������ ������������
	/// \param number �����, ��������� �������������
	void setDialedNumber(const std::string& number);

	/// ���������� ����� ������� ��������
	/// \param number ����� ������� ��������
	void setNativeNumber(const std::string& number);

	/// �������� �����, ������� ������ ������������
	const std::string& getDialedNumber() const;

	/// �������� ����� ������� ��������
	const std::string& getNativeNumber() const;

	/// �������� ���� ������ ��������
	const TelephoneDB& getDataBase() const;

	/// �������� ������� � ������ ���������
	void addContact(const std::string& firstName, const std::string& lastName, const std::string& number);

	/// �������� ������� � ������ ���������
	void addContact(const Contact& contact);

	/// ��������� ������� �� ���� ���������
	void removeContact(const std::string& firstName, const std::string& lastName);

	/// ��������� ������� �� ���� ���������
	void removeContact(const Contact& contact);
	
	/// ��������� ��������� text �� ����� number
	void sendMessage(const std::string& number, const std::string& text);

	/// ��������� ������ �� ����� mDialedNumber
	void call();

	/// ������� �������� �����
	void accept();

	/// �������� �������� �����
	void decline();

	/// �������������� � ������
	void connect();

	/// ������������� (�������� ������� �����)
	void disconnect();

	/// ���� �� ����� ����� ����������
	bool isConnected() const;

	/// ����� �� �������
	bool isBusy() const;

	/// ���� �� �������� ������
	bool isGettingCall() const;

	/// �������� �������� ������
	void getCall(const std::string& caller);

	/// �������� ���������
	void getMessage(const std::string& sender, const std::string& text);

	/// �������� ��� ���������
	std::string getCaller() const;

	/// ��� �� ����� ������� ��������
	void setCalling(bool flag);

	/// ��� �� ��������� ������
	bool isCalling() const;

	/// ��������� �� ������� � ���� ������� (�������� �� � �������)
	bool isInConnectionZone() const;

	/// ��������� ������� � �������
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
	TelephoneLine&					mTelephoneLine; ///< ���������� �����, ���������� �������
	std::weak_ptr<SwitchingCenter>	mSwitchingCenter; ///< ���, � ������� ������ �������
	TelephoneDB						mDataBase; ///< ���� ������ (�������� � ������� �������)
	std::string						mNativeNumber; ///< ����� ������� ��������
	std::string						mDialedNumber; ///< ������� ��������� �����

	std::atomic<bool>				mIsCalling; ///< ��� �� ����� ������� ��������
	std::atomic<bool>				mIsConnected; ///< ����������� �� ����� ����� ����������
	std::atomic<bool>				mIsGettingCall; ///< ���� �� �������� �����

	Timer							mTimer; ///< ������ ��� ������� ������������ ������
	std::string						mCaller; ///< ����� ��������, � �������� �������� �����

	StateStack						mStateStack; ///< ���� ��������� (����) ���� ���� ��������
	sf::Vector2f					mPosition; ///< ������� �������� �� ������
	sf::Vector2f					mSize; ///< ������ ��������
	std::string						mStateParam; ///< ���������� ��� �������� ����� �����������
};