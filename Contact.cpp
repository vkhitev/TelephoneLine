#include "Contact.h"


Contact::Contact()
	: mFirstName()
	, mLastName()
	, mNumber()
{
}

Contact::Contact(const std::string& firstName, const std::string& lastName, const std::string& number)
	: mFirstName(firstName)
	, mLastName(lastName)
	, mNumber(number)
{
}

void Contact::setFirstName(const std::string& firstName)
{
	mFirstName = firstName;
}

void Contact::setLastName(const std::string& lastName)
{
	mLastName = lastName;
}

void Contact::setNumber(const std::string& number)
{
	mNumber = number;
}

const std::string& Contact::getFirstName() const
{
	return mFirstName;
}

const std::string& Contact::getLastName() const
{
	return mLastName;
}

const std::string& Contact::getNumber() const
{
	return mNumber;
}

std::string Contact::getFullName() const
{
	return mFirstName + " " + mLastName;
}

bool operator<(const Contact& a, const Contact& b)
{
	if (a.mFirstName == b.mFirstName)
		return a.mLastName < b.mLastName;
	else
		return a.mFirstName < b.mFirstName;
}