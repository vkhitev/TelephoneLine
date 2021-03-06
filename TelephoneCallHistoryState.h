#pragma once

#include "TelephoneState.h"
#include <vector>

class TelephoneCallHistoryState final : public TelephoneState
{
public:
	TelephoneCallHistoryState(StateStack& stack, AppContext context, Telephone& mParent);

	virtual void draw() const override;
	virtual bool update(sf::Time dt) override;
	virtual bool handleEvent(const sf::Event& event) override;

private:
	std::vector<GUI::Container> mPages;
	int							mCurrentPage;
};