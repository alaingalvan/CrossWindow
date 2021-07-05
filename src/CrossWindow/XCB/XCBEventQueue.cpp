#include "XCBEventQueue.h"
#include "../Common/Init.h"

namespace xwin
{
EventQueue::EventQueue() {}

void EventQueue::update()
{
    const XWinState& xwinState = getXWinState();
    xcb_connection_t* connection = xwinState.connection;
    xcb_flush(connection);
    xcb_wait_for_event(connection);
    xcb_generic_event_t* e;
    while (xcb_generic_event_t* e = xcb_poll_for_event(connection))
    {
        pushEvent(e);
    }
}

const Event& EventQueue::front() { return mQueue.front(); }

void EventQueue::pop() { mQueue.pop(); }

bool EventQueue::empty() { return mQueue.empty(); }

Key getKey(xcb_keycode_t detail)
{
    Key d = Key::KeysMax;

    switch (detail)
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
    return d;
}

void EventQueue::pushEvent(const xcb_generic_event_t* event)
{
    Window* window = nullptr;
    uint8_t event_code = event->response_type & 0x7f;

    Event e = Event(EventType::None, window);

    switch (event_code)
    {
    case XCB_CONFIGURE_NOTIFY:
    {
        e = Event(EventType::Create, window);
        break;
    }
    case XCB_EXPOSE:
    {
        xcb_expose_event_t* expose = (xcb_expose_event_t*)event;
        e = Event(ResizeData(expose->width, expose->height, true), window);
        break;
    }
    case XCB_RESIZE_REQUEST:
    {
        xcb_resize_request_event_t* resize = (xcb_resize_request_event_t*)event;
        e = Event(ResizeData(resize->width, resize->height, false), window);
        break;
    }
    case XCB_ENTER_NOTIFY:
    {
        e = Event(FocusData(true), window);
        break;
    }
    case XCB_LEAVE_NOTIFY:
    {
        e = Event(FocusData(false), window);
        break;
    }
    case XCB_CLIENT_MESSAGE:
    {
        // Maximize / Minimize...
        break;
    }
    case XCB_BUTTON_PRESS:
    {
        xcb_button_press_event_t* bp = (xcb_button_press_event_t*)event;

        bool control = bp->state & XCB_MOD_MASK_CONTROL;
        bool shift = bp->state & XCB_MOD_MASK_SHIFT;
        bool lock = bp->state & XCB_MOD_MASK_LOCK;
        ModifierState mods = ModifierState(control, lock, shift, false);

        if (bp->state & XCB_BUTTON_MASK_1)
        {
            mQueue.emplace(
                MouseInputData(MouseInput::Left, ButtonState::Pressed, mods),
                window);
        }
        if (bp->state & XCB_BUTTON_MASK_2)
        {
            mQueue.emplace(
                MouseInputData(MouseInput::Right, ButtonState::Pressed, mods),
                window);
        }
        if (bp->state & XCB_BUTTON_MASK_3)
        {
            mQueue.emplace(
                MouseInputData(MouseInput::Middle, ButtonState::Pressed, mods),
                window);
        }
        if (bp->state & XCB_BUTTON_MASK_4)
        {
            mQueue.emplace(
                MouseInputData(MouseInput::Button4, ButtonState::Pressed, mods),
                window);
        }
        if (bp->state & XCB_BUTTON_MASK_5)
        {
            mQueue.emplace(
                MouseInputData(MouseInput::Button5, ButtonState::Pressed, mods),
                window);
        }
        break;
    }
    case XCB_BUTTON_RELEASE:
    {
        xcb_button_release_event_t* br = (xcb_button_release_event_t*)event;

        bool control = br->state & XCB_MOD_MASK_CONTROL;
        bool shift = br->state & XCB_MOD_MASK_SHIFT;
        bool lock = br->state & XCB_MOD_MASK_LOCK;
        ModifierState mods = ModifierState(control, lock, shift, false);

        if (br->state & XCB_BUTTON_MASK_1)
        {
            mQueue.emplace(
                MouseInputData(MouseInput::Left, ButtonState::Pressed, mods),
                window);
        }
        if (br->state & XCB_BUTTON_MASK_2)
        {
            mQueue.emplace(
                MouseInputData(MouseInput::Right, ButtonState::Pressed, mods),
                window);
        }
        if (br->state & XCB_BUTTON_MASK_3)
        {
            mQueue.emplace(
                MouseInputData(MouseInput::Middle, ButtonState::Pressed, mods),
                window);
        }
        if (br->state & XCB_BUTTON_MASK_4)
        {
            mQueue.emplace(
                MouseInputData(MouseInput::Button4, ButtonState::Pressed, mods),
                window);
        }
        if (br->state & XCB_BUTTON_MASK_5)
        {
            mQueue.emplace(
                MouseInputData(MouseInput::Button5, ButtonState::Pressed, mods),
                window);
        }
        break;
    }
    case XCB_MOTION_NOTIFY:
    {
        xcb_motion_notify_event_t* motion = (xcb_motion_notify_event_t*)event;

        e = Event(MouseMoveData(motion->event_x, motion->event_y,
                                motion->root_x, motion->root_y, 0, 0),
                  window);
        break;
    }
    case XCB_KEY_PRESS:
    {
        const xcb_key_press_event_t* key = (xcb_key_press_event_t*)event;

        bool control = key->state & XCB_MOD_MASK_CONTROL;
        bool shift = key->state & XCB_MOD_MASK_SHIFT;
        bool lock = key->state & XCB_MOD_MASK_LOCK;
        ModifierState mods = ModifierState(control, lock, shift, false);

        e = Event(KeyboardData(getKey(key->detail), ButtonState::Pressed, mods),
                  window);
        break;
    }
    case XCB_KEY_RELEASE:
    {
        const xcb_key_release_event_t* key =
            (const xcb_key_release_event_t*)event;

        bool control = key->state & XCB_MOD_MASK_CONTROL;
        bool shift = key->state & XCB_MOD_MASK_SHIFT;
        bool lock = key->state & XCB_MOD_MASK_LOCK;
        ModifierState mods = ModifierState(control, lock, shift, false);

        e = Event(KeyboardData(getKey(key->detail), ButtonState::Pressed, mods),
                  window);

        break;
    }

    default:
        break;
    }
    if (e.type != EventType::None)
    {
        mQueue.emplace(e);
    }
}
}