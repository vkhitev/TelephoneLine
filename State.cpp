#include "State.h"
#include "StateStack.h"

#include <SFML/Window/Event.hpp>

State::State(StateStack& stack, AppContext context)
	: mStack(&stack)
	, mContext(context)
{
}

void State::requestStackPush(States::ID stateID)
{
	mStack->pushState(stateID);
}

void State::requestStackPop()
{
	mStack->popState();
}

void State::requestStateClear()
{
	mStack->clearStates();
}

AppContext State::getContext() const
{
	return mContext;
}