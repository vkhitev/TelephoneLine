/**
*
* \class Message
*
* \brief �������� ���������� �� ���-���������
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

class Message
{
public:
	enum State    ///< ��� ���������
	{
		Imcoming, ///< ��������
		Outgoing, ///< ���������
	};

public:
	/// ������� ������
	/// \param state ��� ������ (��������/���������/�����������)
	/// \param caller ����� ���������
	/// \param time ����� ������ ������
	/// \param duration ������������ ������
	Message(State state, const std::string& sender, const std::string& time, const std::string& text);

	/// \return ��� ������
	State getState() const;

	/// \return ����� ���������
	const std::string& getSender() const;

	/// \return ����� ������ ������
	const std::string& getTime() const;

	/// \return ����� ���������
	const std::string& getText() const;

	/// ���������� ��� ������
	void setState(State state);

	/// ���������� ����� ���������
	void setSender(const std::string& sender);

	/// ���������� ����� ������ ������
	/// ������ - dd.mm.yyyy hh:mm:ss
	void setTime(const std::string& time);

	/// ���������� ����� ���������
	void setText(const std::string& text);

private:
	/// �������� ������� �� ����������
	bool isTimeValid(const std::string& time) const;

	State			mState; ///< ��� (�������� ��� ��������� ���������)
	std::string		mSender; ///< ������ ��� ��������, ������� ������ (�������� �������)
	std::string		mCallTime; ///< �����, � ������� ������ ��� ���� ���������
	std::string		mText; ///< ����� ���������
};