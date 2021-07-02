#include "XCBEventQueue.h"
#include "../Common/Init.h"
namespace xwin
{
EventQueue::EventQueue()
{

}

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

void EventQueue::pushEvent(const xcb_generic_event_t* event)
{
    Window* window = nullptr;
    uint8_t event_code = event->response_type & 0x7f;
    switch (event_code)
    {
    case XCB_CONFIGURE_NOTIFY:
    {
        mQueue.emplace(xwin::EventType::Create, window);
        break;
    }
    case XCB_EXPOSE:
    {
        // TODO: Resize window
        break;
    }
    case XCB_ENTER_NOTIFY:
    {
        // focus
        break;
    }
    case XCB_LEAVE_NOTIFY:
    {
        // lose focus
        break;
    }
    case XCB_CLIENT_MESSAGE:
    {
        break;
    }
    case XCB_KEY_PRESS:
    {
        xcb_key_press_event_t* kp = (xcb_key_press_event_t*)event;
        break;
    }
    case XCB_KEY_RELEASE:
    {
        const xcb_key_release_event_t* key =
            (const xcb_key_release_event_t*)event;

        Key d = Key::KeysMax;

        switch (key->detail)
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

        mQueue.emplace(KeyboardData(d, ButtonState::Pressed, ModifierState()),
                       window);

        break;
    }
    case XCB_BUTTON_PRESS:
    {
        xcb_button_press_event_t* bp = (xcb_button_press_event_t*)event;

        switch (bp->detail)
        {
        case 4: // wheel button up

            break;
        case 5: // wheel button down

            break;
        default:

            break;
        }
        break;
    }
    case XCB_BUTTON_RELEASE:
    {
        xcb_button_release_event_t* br = (xcb_button_release_event_t*)event;

        break;
    }

    default:
        break;
    }
}
}