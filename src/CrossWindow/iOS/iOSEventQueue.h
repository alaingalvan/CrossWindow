#pragma once

#include "../Common/Event.h"
#include "../Common/Init.h"
#include <queue>

namespace xwin
{
  struct MacEvent
  {

  }

  class IOSEventQueue
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

  typedef IOSEventQueue EventQueueDelegate;
}