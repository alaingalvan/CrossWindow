#include "EventQueue.h"

namespace xwin
{
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
}