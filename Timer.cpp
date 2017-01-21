#include "Timer.h"
#include <iostream>

using namespace std::chrono;

Timer::Timer()
	: mStart(high_resolution_clock::now())
{
}

void Timer::reset()
{
	mStart = high_resolution_clock::now();
}

milliseconds Timer::elapsedMS() const
{
	auto duration = high_resolution_clock::now() - mStart;
	return duration_cast<milliseconds>(duration);
}

seconds Timer::elapsedS() const
{
	auto duration = high_resolution_clock::now() - mStart;
	return duration_cast<seconds>(duration);
}

minutes Timer::elapsedM() const
{
	auto duration = high_resolution_clock::now() - mStart;
	return duration_cast<minutes>(duration);
}

std::ostream& operator<<(std::ostream& out, const Timer& timer)
{
	return out << timer.elapsedMS().count();
}