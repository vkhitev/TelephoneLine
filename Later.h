/**
*
* \author Хитёв Владислав
*
* \version 6.0
*
* \date 2015/12/01
*
*/

#pragma once

#include <functional>
#include <chrono>
#include <future>

template <class callable, class... arguments>
void Later(int after, bool async, callable&& f, arguments&&... args)
{
	std::function<typename std::result_of<callable(arguments...)>::type()>
		task(std::bind(std::forward<callable>(f), std::forward<arguments>(args)...));

	if (async)
	{
		std::thread([after, task]()
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(after));
			task();
		}).detach();
	}
	else
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(after));
		task();
	}
}

template <class obj, class callable, class... arguments>
void Later(int after, bool async, obj& object, callable&& f, arguments&&... args)
{
	std::function<typename std::result_of<callable(obj, arguments...)>::type()>
		task(std::bind(std::forward<callable>(f), std::forward<obj*>(&object), std::forward<arguments>(args)...));

	if (async)
	{
		std::thread([after, task]()
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(after));
			task();
		}).detach();
	}
	else
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(after));
		task();
	}
}