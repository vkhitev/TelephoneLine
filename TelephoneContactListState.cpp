#include "TelephoneContactListState.h"
#include "Telephone.h"

using namespace GUI;

TelephoneContactListState::TelephoneContactListState(StateStack& stack, AppContext context, Telephone& parent)
	: TelephoneState(stack, context, parent)
	, mPages()
	, mCurrentPage(0)
{
	auto& window = getContext().getWindow();
	auto& font = getContext().getFonts().get(Fonts::Main);
	auto& contacts = mTelephone.getDataBase().getContacts();

	float xOffset = 20.f;
	float yOffset = 0.f;

	const int maxContactsOnPage = 7;
	int currentContact = 0;
	int currentPage = 0;
	mPages.push_back(Container(window));

	for (const auto& contact : contacts)
	{
		sf::Vector2f defaultPosition(xOffset, yOffset + 18.f);

		auto button = makeButton({ 310.f, 60.f }, defaultPosition, "");
		button->setOverBackgroundColor({ 50, 50, 50, 50 });
		button->setBackgroundColor({ 50, 50, 50, 100 });
		button->setCallback([this, contact]()
		{
			requestStackPop();
			requestStackPush(States::Contact);
			mTelephone.setStateParam(contact.getNumber());
		});

		auto name = makeLabel(defaultPosition + sf::Vector2f(10.f, 2.f), contact.getFullName(), 28U, false);
		
		auto number = makeLabel(defaultPosition + sf::Vector2f(10.f, 35.f), contact.getNumber(), 18U, false);

		yOffset += 67.f;

		mPages[currentPage].pack(button);
		mPages[currentPage].pack(name);
		mPages[currentPage].pack(number);

		currentContact++;
		if (currentContact == maxContactsOnPage)
		{
			yOffset = 0.f;
			currentContact = 0;
			currentPage++;
			mPages.push_back(Container(window));

		}
	}

	auto callingPanel = makeButton({ 100, 40 }, { 10, 512 }, "dial", [this]()
	{
		requestStackPop();
		requestStackPush(States::CallingPanel);
	});

	callingPanel->setTextSize(22U);
	callingPanel->setOverTextColor({ 185, 122, 87 });
	mContainer.pack("callingPanel", callingPanel);


	auto callHistory = makeButton({ 100, 40 }, { 240, 515 }, "history", [this]()
	{
		requestStackPop();
		requestStackPush(States::CallHistory);
	});

	callHistory->setTextSize(22U);
	callHistory->setOverTextColor({ 185, 122, 87 });
	mContainer.pack("callHistory", callHistory);


	auto next = makeButton({ 50, 40 }, { 173, 515 }, "->", [this]()
	{
		auto next = mContainer.get<Button>("next");
		auto prev = mContainer.get<Button>("prev");
		mCurrentPage++;
		if (mCurrentPage == mPages.size() - 1)
		{
			next->setClickActive(false);
		}
		prev->setClickActive(true);
	});

	next->setTextSize(35U);
	next->setOverTextColor({ 185, 122, 87 });
	next->setUnactiveTextColor({ 200, 200, 200 });
	if (mPages.size() <= 1)
	{
		next->setClickActive(false);
	}
	mContainer.pack("next", next);

	auto prev = makeButton({ 50, 40 }, { 123, 515 }, "<-", [this]()
	{
		auto next = mContainer.get<Button>("next");
		auto prev = mContainer.get<Button>("prev");
		mCurrentPage--;
		if (mCurrentPage == 0)
		{
			prev->setClickActive(false);
		}
		next->setClickActive(true);
	});

	prev->setTextSize(35U);
	prev->setOverTextColor({ 185, 122, 87 });
	prev->setUnactiveTextColor({ 200, 200, 200 });
	prev->setClickActive(false);
	mContainer.pack("prev", prev);
}

void TelephoneContactListState::draw() const
{
	TelephoneState::draw();
	mPages[mCurrentPage].draw();
}

bool TelephoneContactListState::update(sf::Time dt)
{
	TelephoneState::update(dt);
	mPages[mCurrentPage].update(dt);
	return true;
}

bool TelephoneContactListState::handleEvent(const sf::Event& event)
{
	mContainer.handleEvent(event);
	mPages[mCurrentPage].handleEvent(event);
	return true;
}