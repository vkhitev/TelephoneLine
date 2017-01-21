/**
*
* \class RegisteredCall
*
* \brief �������� ���������� � ����������� ������ (�������� ��� ���������)
*
* ��������� ��� ������, ��� ��������� (����������), ����� � ������������ ���������.
* ��������� �������� ������������� �������� ��������.
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

class RegisteredCall
{
public:
	enum State    ///< ������������ ����� �������
	{
		Imcoming, ///< �������� �����
		Outgoing, ///< ��������� �����
		Missed,   ///< ����������� �����
	};

public:
	/// ������� ������
	/// \param state ��� ������ (��������/���������/�����������)
	/// \param caller ����� ���������
	/// \param time ����� ������ ������
	/// \param duration ������������ ������
	RegisteredCall(State state, const std::string& caller, const std::string& time, unsigned int duration);

	/// \return ��� ������
	State getState() const;

	/// \return ��� ������ ��� ������
	std::string getStrState() const;

	/// \return ����� ���������
	const std::string& getCaller() const;

	/// \return ����� ������ ������
	const std::string& getTime() const;

	/// \return ������������ ������
	unsigned int getDuration() const;

	/// ���������� ��� ������
	void setState(State state);

	/// ���������� ����� ���������
	void setCaller(const std::string& caller);

	/// ���������� ����� ������ ������
	/// ������ - dd.mm.yyyy hh:mm:ss
	void setTime(const std::string& time);

	/// ���������� ������������ �����
	void setDuration(unsigned int duration);

private:
	/// �������� ������� �� ����������
	bool isTimeValid(const std::string& time) const;

	State			mState; ///< ��� ������
	std::string		mCaller; ///< ������ ��� ��������, ������� ������ (�������� �������)
	std::string		mCallTime; ///< �����, � ������� ������������ ����������
	unsigned int	mCallDuration; ///< ������������ ������
};