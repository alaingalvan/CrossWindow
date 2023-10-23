#pragma once

#include "../Common/Event.h"

#include <queue>
#include <wayland-client-core.h>

namespace xwin
{
class Window;

/**
 * Events - https://xcb.freedesktop.org/tutorial/events/
 */
class EventQueue
{
  public:
    EventQueue();

    void update();

    const Event& front();

    void pop();

    bool empty();

  protected:
    // void pushEvent();
    struct wl_event_queue* event_queue;

    std::queue<Event> mQueue;
};
}
