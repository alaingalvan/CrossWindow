#pragma once

#include <android/input.h>

#include "../Common/Init.h"
#include "../Common/Event.h"

#include <queue>

namespace xwin
{
  class AndroidEventQueue
  {
  public:
    void update();

    const Event &front();

    void pop();

    bool empty();

  protected:
    /**
     * https://developer.android.com/ndk/reference/group/input
     */ 
    void pushEvent(AInputEvent e);

    std::queue<Event> mQueue;
  };

  typedef AndroidEventQueue EventQueueDelegate;
}