#include "XLibEventQueue.h"
#include "../Common/Window.h"
#include "CrossWindow/Common/WindowDesc.h"
#include <X11/X.h>

namespace xwin
{
void EventQueue::update()
{
    XEvent event;

    while (XPending(mParent->display) > 0)
    {
        XNextEvent(mParent->display, &event);
        pushEvent(&event, mParent);
    }
}

EventQueue::EventQueue() {}

EventQueue::EventQueue(Window* parent) : mParent(parent) {}

const Event& EventQueue::front() { return mQueue.front(); }

void EventQueue::pop() { mQueue.pop(); }

bool EventQueue::empty() { return mQueue.empty(); }

void EventQueue::pushEvent(const XEvent* event, Window* window)
{
    xwin::Event e = xwin::Event(window); // xwin::EventType::None, window);

    switch (event->type)
    {
    case CreateNotify:
    {
        e = xwin::Event(xwin::EventType::Create, window);
        break;
    }
    case ResizeRequest:
    {
        unsigned width, height;
        width = static_cast<unsigned>(event->xconfigure.width);
        height = static_cast<unsigned>(event->xconfigure.height);

        e = xwin::Event(ResizeData(width, height, false), window);
        break;
    }
    case DestroyNotify:
    {
        e = xwin::Event(xwin::EventType::Close, window);
        break;
    }
    case KeyRelease:
    case KeyPress:
    {
        Key d = Key::KeysMax;
        switch (event->xkey.keycode)
        {
        case XK_Escape: // Escape
            d = Key::Escape;
            break;
        case XK_KP_Left: // left arrow key
            d = Key::Left;
            break;
        case XK_KP_Right: // right arrow key
            d = Key::Right;
            break;
        case XK_KP_Space: // space bar
            d = Key::Space;
            break;
        }
        break;

        e = xwin::Event(KeyboardData(d,
                                     event->type == KeyPress
                                         ? ButtonState::Pressed
                                         : ButtonState::Released,
                                     ModifierState()),
                        window);
    }
    }
}
}
