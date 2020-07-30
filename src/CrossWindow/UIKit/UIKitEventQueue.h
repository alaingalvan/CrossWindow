#pragma once

#include "../Common/Event.h"
#include "../Common/Init.h"
#include <queue>

namespace xwin
{
struct MacEvent
{
	
};

class EventQueue
{
public:
	void update();
	
	const Event &front();
	
	void pop();
	
	bool empty();
	
protected:
	void pushEvent(MacEvent me);
	
	std::queue<Event> mQueue;
};
}
