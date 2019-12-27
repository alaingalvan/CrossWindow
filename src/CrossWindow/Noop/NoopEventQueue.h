#pragma once

#include "../Common/Event.h"

namespace xwin
{
  class EventQueue
  {
    public:
    EventQueue();

    void update();

    const Event& front();

    void pop();

	bool empty();

    protected:
    Event e = Event(EventType::EventTypeMax, nullptr);
  };

}