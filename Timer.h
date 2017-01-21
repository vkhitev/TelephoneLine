/**
*
* \class Timer
*
* \brief ������� �����.
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
#include <chrono>
#include <ostream>

class Timer
{
public:
	Timer();

	/// �������� ������
	void reset();

	/// ���������� ����� � �������������
	std::chrono::milliseconds elapsedMS() const;

	/// ���������� ����� � ��������
	std::chrono::seconds elapsedS() const;

	/// ���������� ����� � �������
	std::chrono::minutes elapsedM() const;

	/// ������� � ����� ����� � �������������
	friend std::ostream& operator<<(std::ostream& out, const Timer& timer);
private:
	/// ����� ������ �������
	std::chrono::high_resolution_clock::time_point mStart;
};