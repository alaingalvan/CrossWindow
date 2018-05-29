#pragma once

#include "../Common/Event.h"

#include <queue>

namespace xwin
{
  struct MacEvent
  {

  }

  class MacOSEventQueue
  {
  public:
    bool update();

    const Event &front();

    void pop();

    bool empty();

  protected:
    void pushEvent(MacEvent me);

    std::queue<Event> mQueue;
  };

  typedef MacOSEventQueue EventQueueDelegate;
}