#pragma once

#include <android/input.h>

#include "../Common/Event.h"

#include <queue>

namespace xwin
{
  class AndroidEventQueue
  {
  public:
    bool update();

    const Event &front();

    void pop();

    bool empty();

  protected:
    void pushEvent(AInputEvent e);

    std::queue<Event> mQueue;
  };

  typedef AndroidEventQueue EventQueueDelegate;
}