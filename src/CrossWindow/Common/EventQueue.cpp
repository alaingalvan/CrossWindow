#include "EventQueue.h"

namespace xwin
{
    EventQueue::EventQueue()
    {
    }
    
    bool EventQueue::update()
    {
        return mDelegate.update();
    }

    const Event& EventQueue::front()
    {
        return mDelegate.front();
    }

    void EventQueue::pop()
    {
        mDelegate.pop();
    }
    bool EventQueue::empty()
    {
        return mDelegate.empty();
    }
}