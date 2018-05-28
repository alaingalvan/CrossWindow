#pragma once

#include "../Common/Event.h"

namespace xwin
{
  class NoopEventQueue
  {
    public:
    bool update();

    const Event& front();

    void pop();
  };

  typedef NoopEventQueue EventQueueDelegate;
}