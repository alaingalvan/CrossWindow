#pragma once

#include "../Common/Event.h"
#include "../Common/Init.h"
#include <queue>

namespace xwin
{

class EventQueue
{
public:
	void update();
	
	const Event &front();
	
	void pop();
	
	bool empty();
	
	void pushEvent(Event e);
	
	std::queue<Event> mQueue;
};
}
