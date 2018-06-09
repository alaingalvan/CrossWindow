#include "XCBEventQueue.h"

namespace xwin
{
  XCBEventQueue::XCBEventQueue()
  {

  }

  bool XCBEventQueue::update()
  {
        xcb_generic_event_t *event;

        if (demo->pause) {
            event = xcb_wait_for_event(demo->connection);
        } else {
            event = xcb_poll_for_event(demo->connection);
        }
        while (event) {
            pushEvent(event);
            free(event);
            event = xcb_poll_for_event(demo->connection);
        }

        curFrame++;
        if (demo->frameCount != INT32_MAX && demo->curFrame == demo->frameCount) demo->quit = true;
  }

    void XCBEventQueue::pushEvent(const xcb_generic_event_t *event) {
    uint8_t event_code = event->response_type & 0x7f;
    switch (event_code) {
        case XCB_EXPOSE:
            // TODO: Resize window
            break;
            case XCB_ENTER_NOTIFY: {
                //focus
                break;
            }
            case XCB_LEAVE_NOTIFY: {
                //lose focus
                break;
            }
        case XCB_CLIENT_MESSAGE:
            if ((*(xcb_client_message_event_t *)event).data.data32[0] == (*demo->atom_wm_delete_window).atom)
            {
                //quit
            }
            break;
            case XCB_KEY_PRESS: {
                xcb_key_press_event_t *kp = (xcb_key_press_event_t *)event
                   break;
            }
        case XCB_KEY_RELEASE: {
            const xcb_key_release_event_t *key = (const xcb_key_release_event_t *)event;

            switch (key->detail) {
                case 0x9:  // Escape

                    break;
                case 0x71:  // left arrow key

                    break;
                case 0x72:  // right arrow key

                    break;
                case 0x41:  // space bar

                    break;
            }
            break;
        } 
        case XCB_BUTTON_PRESS: {
            xcb_button_press_event_t *bp = (xcb_button_press_event_t *)event;

            switch (bp->detail) {
            case 4: //wheel button up

                break;
            case 5: //wheel button down

                break;
            default:

                break;
            }
            break;
        }
        case XCB_BUTTON_RELEASE: {
            xcb_button_release_event_t *br = (xcb_button_release_event_t *)event;

            break;
        }
        case XCB_CONFIGURE_NOTIFY: {

            break;
        } 
        default:
            break;
    }
}
}