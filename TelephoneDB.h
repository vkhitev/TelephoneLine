/**
*
* \class TelephoneDB
*
* \brief ���� ������ ��������, ������� �������� �������� � ������� �������.
*
* ��������� �������� ������ ��������� � ������� �������, � ����� �������������
* ��������� � ������ ������� ����� ��������.
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

#include "Contact.h"
#include "RegisteredCall.h"
#include "Message.h"

#include <set>
#include <deque>

class TelephoneDB
{
public:
	/// ������ �� ��������
	TelephoneDB();

	/// ���������������� �����
	/// \param state ��� ������ (��������/���������/�����������)
	/// \param caller ����� ���������
	/// \param time ����� ������ ������
	/// \param duration ������������ ������
	void registerCall(RegisteredCall::State state, const std::string& caller, const std::string& time, unsigned int duration);

	void registerCallWithNumber(const RegisteredCall& call);

	/// ���������������� ���������
	/// \param state ��� ��������� (��������/���������)
	/// \param sender ����� �����������
	/// \param time ����� ��������
	/// \param text ����� ���������
	void registerMessage(Message::State state, const std::string& sender, const std::string& time, const std::string& text);

	void registerMessageWithNumber(const Message& message);

	/// �������� ������� � ������ ���������
	void addContact(const std::string& firstName, const std::string& lastName, const std::string& number);

	/// �������� ������� � ������ ���������
	void addContact(const Contact& contact);

	/// ��������� ������� �� ���� ���������
	void removeContact(const std::string& firstName, const std::string& lastName);

	/// ��������� ������� �� ���� ���������
	void removeContact(const Contact& contact);

	/// \return ������ ���������
	const std::set<Contact> getContacts() const;

	/// \return ������ ����������� �������
	const std::deque<RegisteredCall> getCalls() const;

	/// \return ������ ���������
	const std::deque<Message> getMessages() const;

	/// ������� ��� �� ������ � ������ ���������
	std::string findName(const std::string& number) const;

private:
	/// �������� ������ �� ����� (� ������ ������� � ����������), ���� ������� ��� �������� � ����
	void replaceNumberInCallsAndMessages(const Contact& contact);

	/// �������� ����� �� ������ (� ������ ������� � ����������), ���� ������� ��� ����� �� ����
	void replaceCallerInCallsAndMessages(const Contact& contact);

	std::set<Contact>			mContacts; ///< ������ ���������
	std::deque<RegisteredCall>	mRegisteredCalls; ///< ������ �������: ��������, ���������, �����������
	std::deque<Message>			mMessages; ///< ������ ���������: ��������, ���������
};