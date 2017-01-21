#include "RegisteredCall.h"
#include "Utility.h"

#include <cassert>
#include <regex>

RegisteredCall::RegisteredCall(State state, const std::string& caller, const std::string& time, unsigned int duration)
	: mState(state)
	, mCaller(caller)
	, mCallTime(time)
	, mCallDuration(duration)
{
	assert(isTimeValid(time) && "Time is not valid");
}


RegisteredCall::State RegisteredCall::getState() const
{
	return mState;
}

std::string RegisteredCall::getStrState() const
{
	switch (mState)
	{
		case State::Imcoming:
			return "Imcoming";
		case State::Outgoing:
			return "Outgoing";
		case State::Missed:
			return "Missed";
		default:
			return "";
	}
}

const std::string& RegisteredCall::getCaller() const
{
	return mCaller;
}

const std::string& RegisteredCall::getTime() const
{
	return mCallTime;
}

unsigned int RegisteredCall::getDuration() const
{
	return mCallDuration;
}

void RegisteredCall::setState(State state)
{
	mState = state;
}

void RegisteredCall::setCaller(const std::string& caller)
{
	mCaller = caller;
}

void RegisteredCall::setDuration(unsigned int duration)
{
	mCallDuration = duration;
}

void RegisteredCall::setTime(const std::string& time)
{
	assert(isTimeValid(time) && "Time is not valid");
	mCallTime = time;
}

bool RegisteredCall::isTimeValid(const std::string& time) const
{
	std::regex e("\\d{2}.\\d{2}.\\d{4} \\d{2}:\\d{2}:\\d{2}");
	return std::regex_match(time, e);
}