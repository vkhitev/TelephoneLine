#include "Message.h"
#include "Utility.h"

#include <cassert>
#include <regex>

Message::Message(State state, const std::string& caller, const std::string& time, const std::string& text)
	: mState(state)
	, mSender(caller)
	, mCallTime(time)
	, mText(text)
{
	assert(isTimeValid(time) && "Time is not valid");
}

Message::State Message::getState() const
{
	return mState;
}

const std::string& Message::getSender() const
{
	return mSender;
}

const std::string& Message::getTime() const
{
	return mCallTime;
}

const std::string& Message::getText() const
{
	return mText;
}

void Message::setState(State state)
{
	mState = state;
}

void Message::setSender(const std::string& sender)
{
	mSender = sender;
}

void Message::setTime(const std::string& time)
{
	assert(isTimeValid(time) && "Time is not valid");
	mCallTime = time;
}

void Message::setText(const std::string& text)
{
	mText = text;
}

bool Message::isTimeValid(const std::string& time) const
{
	std::regex e("\\d{2}.\\d{2}.\\d{4} \\d{2}:\\d{2}:\\d{2}");
	return std::regex_match(time, e);
}