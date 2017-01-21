#include "TelephoneDB.h"

#include <algorithm>

TelephoneDB::TelephoneDB()
	: mContacts()
	, mRegisteredCalls()
	, mMessages()
{
}

void TelephoneDB::registerCall(RegisteredCall::State state, const std::string& caller, const std::string& time, unsigned int duration)
{
	std::string name = findName(caller);
	mRegisteredCalls.emplace_front(state, name, time, duration);
}

void TelephoneDB::registerMessage(Message::State state, const std::string& sender, const std::string& time, const std::string& text)
{
	std::string name = findName(sender);
	mMessages.emplace_front(state, name, time, text);
}

void TelephoneDB::registerCallWithNumber(const RegisteredCall& call)
{
	std::string name = findName(call.getCaller());
	mRegisteredCalls.emplace_front(call.getState(), name, call.getTime(), call.getDuration());
}

void TelephoneDB::registerMessageWithNumber(const Message& message)
{
	std::string name = findName(message.getSender());
	mMessages.emplace_front(message.getState(), name, message.getTime(), message.getText());
}

std::string TelephoneDB::findName(const std::string& number) const
{
	for (const Contact& contact : mContacts)
	{
		if (contact.getNumber() == number)
		{
			return contact.getFullName();
		}
	}
	return number;
}

void TelephoneDB::addContact(const std::string& firstName, const std::string& lastName, const std::string& number)
{
	addContact(Contact(firstName, lastName, number));
}

void TelephoneDB::addContact(const Contact& contact)
{
	mContacts.insert(contact);
	replaceNumberInCallsAndMessages(contact);
}

void TelephoneDB::removeContact(const std::string& firstName, const std::string& lastName)
{
	auto found = std::find_if(cbegin(mContacts), cend(mContacts), [&](const Contact& contact)
	{
		return (contact.getFirstName() == firstName && contact.getLastName() == lastName);
	});

	if (found != cend(mContacts))
	{
		removeContact(*found);
	}
}

void TelephoneDB::removeContact(const Contact& contact)
{
	mContacts.erase(contact);
	replaceCallerInCallsAndMessages(contact);
}

const std::set<Contact> TelephoneDB::getContacts() const
{
	return mContacts;
}

const std::deque<RegisteredCall> TelephoneDB::getCalls() const
{
	return mRegisteredCalls;
}

const std::deque<Message> TelephoneDB::getMessages() const
{
	return mMessages;
}

void TelephoneDB::replaceNumberInCallsAndMessages(const Contact& contact)
{
	for (RegisteredCall& call : mRegisteredCalls)
	{
		if (call.getCaller() == contact.getNumber())
		{
			call.setCaller(contact.getFullName());
			return;
		}
	}

	for (Message& message : mMessages)
	{
		if (message.getSender() == contact.getNumber())
		{
			message.setSender(contact.getFullName());
			return;
		}
	}
}

void TelephoneDB::replaceCallerInCallsAndMessages(const Contact& contact)
{
	for (RegisteredCall& call : mRegisteredCalls)
	{
		if (call.getCaller() == contact.getFullName())
		{
			call.setCaller(contact.getNumber());
			return;
		}
	}

	for (Message& message : mMessages)
	{
		if (message.getSender() == contact.getFullName())
		{
			message.setSender(contact.getNumber());
			return;
		}
	}
}