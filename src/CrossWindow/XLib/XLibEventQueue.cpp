#include "XLibEventQueue.h"
#include "../Common/Window.h"
#include "CrossWindow/Common/WindowDesc.h"

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
    switch (event->type)
    {
    case ConfigureNotify:
    {
        WindowDesc desc = window->getDesc();
        if ((desc.width != event->xconfigure.width) ||
            (desc.height != event->xconfigure.height))
        {
            unsigned width, height;
            width = static_cast<unsigned>(event->xconfigure.width);
            height = static_cast<unsigned>(event->xconfigure.height);

            mQueue.emplace(ResizeData(width, height, true), window);
        }
        break;
    }
    case ClientMessage:
    {
        mQueue.emplace(xwin::EventType::Close, window);
        break;
    }
    case KeyPress:
    {
        Key d = Key::KeysMax;
        switch (event->xkey.keycode)
        {
        case 0x9: // Escape
            d = Key::Escape;
            break;
        case XK_KP_Left: // left arrow key
            d = Key::Left;
            break;
        case 0x72: // right arrow key
            d = Key::Right;
            break;
        case 0x41: // space bar
            d = Key::Space;
            break;
        }
        break;

        mQueue.emplace(KeyboardData(d, ButtonState::Pressed, ModifierState()),
                       window);
    }
    }
}
}
