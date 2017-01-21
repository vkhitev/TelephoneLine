/**
*
* \class Contact
*
* \brief �������� ������ ���������� � ���������� ��������
*
* �������� ���, ������� � ����� ��������. ��������� �������� � �������� ��� ��������.
* � �������, ��������, ����� ��������� �������� "�������� �����", "�������������� �����" � ��.
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

#include <string>

class Contact
{
public:
	/// ������� ������ �������
	Contact();

	/// ������� �������
	/// \param firstName ��� ��������
	/// \param lastName ������� ��������
	/// \param number ����� ��������
	Contact(const std::string& firstName, const std::string& lastName, const std::string& number);

	/// ���������� ��� ��������
	void setFirstName(const std::string& firstName);

	/// ���������� ������� ��������
	void setLastName(const std::string& lastName);

	/// ���������� ����� ��������
	void setNumber(const std::string& number);

	/// \return ��� ��������
	const std::string& getFirstName() const;

	/// \return ������� ��������
	const std::string& getLastName() const;

	/// \return ����� ��������
	const std::string& getNumber() const;

	/// \return ��� � �������
	std::string getFullName() const;

	/// ��������� �� ����� � �������
	friend bool operator<(const Contact& a, const Contact& b);

private:

	std::string		mFirstName; ///< ��� ��������
	std::string		mLastName; ///< ������� ��������
	std::string		mNumber; ///< ���������� ����� ��������
};