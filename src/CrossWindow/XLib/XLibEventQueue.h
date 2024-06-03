#pragma once

#include "../Common/Event.h"

#include <queue>

#include <X11/Xlib.h>
#include <X11/keysym.h>

namespace xwin
{
class Window;

class EventQueue
{
  public:
    EventQueue();
    EventQueue(Window* parent);

    void update();

    const Event& front();

    void pop();

    bool empty();

    void pushEvent(const XEvent* event, Window* window);

  protected:
    std::queue<Event> mQueue;
    Window* mParent;
};
}
