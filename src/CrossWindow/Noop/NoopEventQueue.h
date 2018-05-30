#pragma once

#include "../Common/Event.h"

namespace xwin
{
  class NoopEventQueue
  {
    public:
    NoopEventQueue();

    bool update();

    const Event& front();

    void pop();

    protected:
    Event e = Event(EventType::EventTypeMax);
  };

  typedef NoopEventQueue EventQueueDelegate;
}