#pragma once

#include "../Common/Event.h"

#include <xcb/xcb.h>

#include <queue>

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

        const Event &front();

        void pop();

        bool empty();

    protected:
        void pushEvent(const xcb_generic_event_t* e);

        std::queue<Event> mQueue;
    };
}