#pragma once

#include "../Common/Event.h"

#include <queue>

namespace xwin
{
class Window;

/**
 * Events - https://xcb.freedesktop.org/tutorial/events/
 */
class EventQueue
{
  public:
    EventQueue();

    void update();

    const Event& front();

    void pop();

    bool empty();

  protected:
    // void pushEvent();

    std::queue<Event> mQueue;
};
}
