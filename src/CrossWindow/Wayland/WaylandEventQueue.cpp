#include "WaylandEventQueue.h"
#include "../Common/Window.h"
#include "CrossWindow/Common/WindowDesc.h"

namespace xwin
{
EventQueue::EventQueue()
{
    const XWinState& state = getXWinState();
    event_queue = wl_display_create_queue(state.display);
}

void EventQueue::update() {}

const Event& EventQueue::front() { return mQueue.front(); }

void EventQueue::pop() { mQueue.pop(); }

bool EventQueue::empty() { return mQueue.empty(); }
}
