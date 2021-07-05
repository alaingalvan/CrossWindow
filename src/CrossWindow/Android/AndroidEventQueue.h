#pragma once

#include <android/input.h>

#include "../Common/Event.h"
#include "../Common/Init.h"

#include <queue>

namespace xwin
{
/**
 * https://developer.android.com/ndk/reference/group/input
 */
class AndroidEventQueue
{
  public:
    void update();

    const Event& front();

    void pop();

    bool empty();

  protected:
    void pushEvent(AInputEvent e);

    std::queue<Event> mQueue;
};
}