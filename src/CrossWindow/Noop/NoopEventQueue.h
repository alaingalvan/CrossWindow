#pragma once

#include "../Common/Event.h"

namespace xwin
{
  class NoopEventQueue
  {
    public:
    NoopEventQueue();

    void update();

    const Event& front();

    void pop();

	bool empty();

    protected:
    Event e = Event(EventType::EventTypeMax, nullptr);
  };

  typedef NoopEventQueue EventQueueDelegate;
}