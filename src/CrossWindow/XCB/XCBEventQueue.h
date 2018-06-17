#pragma once

#include "../Common/Event.h"

#include <queue>

namespace xwin
{
    class Window;

    /**
     * Events - https://xcb.freedesktop.org/tutorial/events/
     */
    class XCBEventQueue
    {
    public:
        XCBEventQueue();

        void update();

        const Event &front();

        void pop();

        bool empty();

    protected:
        void pushEvent(xcb_generic_event_t me);

        std::queue<Event> mQueue;
    };

    typedef XCBEventQueue EventQueueDelegate;
}