/**
*
* \class SwitchingCenter
*
* \brief ���������� ������� (���) ������������� ����� ����� ����� (���� ��� �����) ����������.
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
	/// ��������� ������ ��� ������. None - ��� ������
	enum ErrorState
	{
		None,
		Unregistered,
		Busy,
		WrongNumber,
		OutOfZone,
	};

public:
	/// ������ ���
	SwitchingCenter(AppContext context);

	/// ������� ������� � ���� ������
	void registerTelephone(const std::shared_ptr<Telephone>& telephone);

	/// ��������� �� ����� � ����
	bool isRegistered(const std::string& number);

	/// ����������� ���������� ����� ����� ���������� � ������������ ����������
	void connect(Telephone& caller, const std::string& number);

	/// ���������� ��������� text �� ����������� sender �� ����� number
	bool sendMessage(Telephone& sender, const std::string& number, const std::string& text);

	std::vector<RegisteredCall> getLateCalls(const std::string& number);
	std::vector<Message> getLateMessages(const std::string& number);

private:
	/// �������� ������ �� ������������ (TODO)
	bool isNumberValid(const std::string& number) const;

	/// �������� ��������� ������ ������, ���� ��� �������
	ErrorState getCallErrorState(const std::string& number);

	/// �������� ��������� ������ �������� ���������, ���� ��� �������
	ErrorState getMessageErrorState(const std::string& number);

	void printError(ErrorState error);

private:
	/// �����. ������ "����� �������� : �������" - ������������������ � ���� ��������
	std::map<std::string, std::weak_ptr<Telephone>> mRegisteredTelephones;

	std::map<std::string, std::vector<RegisteredCall>> mLateCalls; ///< ���������� ������
	std::map<std::string, std::vector<Message>> mLateMessages; ///< ���������� ���������

	const static int sMaxNumberDigits; ///< ������������ ���������� ����� � ������
};