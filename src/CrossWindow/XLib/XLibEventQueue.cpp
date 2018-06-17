#include "XLibEventQueue.h"
#include "../Common/Window.h"

namespace xwin
{
    void XLibEventQueue::update()
    {
        XEvent event;

        while (XPending(demo->display) > 0)
        {
            XNextEvent(demo->display, &event);
            pushEvent(event, mParent);
        }
    }

    void XLibEventQueue::pushEvent(const XEvent *event, Window *window)
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

                mQueue.emplace(ResizeData(width, height), window);
            }
            break;
        }
        case ClientMessage:
        {
            if ((Atom)event->xclient.data.l[0] == demo->xlib_wm_delete_window)
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
            case 0x71: // left arrow key
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

            mQueue.emplace(KeyboardData(d, ButtonState::Pressed, ModifierState()), window);
        }
        }
    }
}