#pragma once

#include "../Common/Event.h"

#include <queue>

namespace xwin
{
class Window;

class XLibEventQueue
{
public:
  void pushEvent(const XEvent *event, Window *window);

protected:
  std::queue<Event> mQueue;
}
}