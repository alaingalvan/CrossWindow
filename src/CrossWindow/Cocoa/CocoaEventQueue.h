#pragma once

#include "../Common/Event.h"
#include "../Common/Init.h"
#include <queue>

namespace xwin
{
struct MacEvent
{
};

/**
 * MacOS Events can be per window virtual functions or received from a queue.
 * Events - https://developer.apple.com/documentation/appkit/nsevent
 */
class EventQueue
{
  public:
    void update();

    const Event& front();

    void pop();

    bool empty();

  protected:
    void pushEvent(MacEvent me);

    std::queue<Event> mQueue;
};
}
