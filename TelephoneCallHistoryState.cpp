#include "TelephoneCallHistoryState.h"
#include "Telephone.h"

using namespace GUI;

TelephoneCallHistoryState::TelephoneCallHistoryState(StateStack& stack, AppContext context, Telephone& parent)
	: TelephoneState(stack, context, parent)
	, mPages()
	, mCurrentPage(0)
{
	auto& window = getContext().getWindow();
	auto& font = getContext().getFonts().get(Fonts::Main);
	auto& calls = mTelephone.getDataBase().getCalls();

	float xOffset = 20.f;
	float yOffset = 0.f;

	const int maxCallsOnPage = 7;
	int currentCall = 0;
	int currentPage = 0;
	mPages.push_back(Container(window));

	for (const auto& call : calls)
	{
		sf::Vector2f defaultPosition(xOffset, yOffset + 18.f);

		auto button = makeButton({ 310.f, 60.f }, defaultPosition, "");
		button->setOverBackgroundColor({ 50, 50, 50, 50 });
		button->setBackgroundColor({ 50, 50, 50, 100 });

		auto name = makeLabel(defaultPosition + sf::Vector2f(10.f, 2.f), call.getCaller(), 28U, false);

		auto state = makeLabel(defaultPosition + sf::Vector2f(10.f, 35.f),
			call.getStrState() + ", " + call.getTime() + ", " + std::to_string(call.getDuration()) + "s", 18U, false);

		yOffset += 67.f;

		mPages[currentPage].pack(button);
		mPages[currentPage].pack(name);
		mPages[currentPage].pack(state);

		currentCall++;
		if (currentCall == maxCallsOnPage)
		{
			yOffset = 0.f;
			currentCall = 0;
			currentPage++;
			mPages.push_back(Container(window));

		}
	}

	auto contacts = makeButton({ 100, 40 }, { 240, 515 }, "contacts", [this]()
	{
		requestStackPop();
		requestStackPush(States::ContactList);
	});

	contacts->setTextSize(22U);
	contacts->setOverTextColor({ 185, 122, 87 });
	mContainer.pack("contacts", contacts);


	auto callingPanel = makeButton({ 100, 40 }, { 10, 512 }, "dial", [this]()
	{
		requestStackPop();
		requestStackPush(States::CallingPanel);
	});

	callingPanel->setTextSize(22U);
	callingPanel->setOverTextColor({ 185, 122, 87 });
	mContainer.pack("callingPanel", callingPanel);


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

void TelephoneCallHistoryState::draw() const
{
	TelephoneState::draw();
	mPages[mCurrentPage].draw();
}

bool TelephoneCallHistoryState::update(sf::Time dt)
{
	TelephoneState::update(dt);
	mPages[mCurrentPage].update(dt);
	return true;
}

bool TelephoneCallHistoryState::handleEvent(const sf::Event& event)
{
	mContainer.handleEvent(event);
	mPages[mCurrentPage].handleEvent(event);
	return true;
}