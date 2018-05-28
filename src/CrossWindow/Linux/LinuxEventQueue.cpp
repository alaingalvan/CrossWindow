#include "LinuxEventQueue.h"

namespace xwin
{
  LinuxEventQueue::LinuxEventQueue()
  {

  }

  bool LinuxEventQueue::update()
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

    void LinuxEventQueue::pushEvent(const xcb_generic_event_t *event) {
    uint8_t event_code = event->response_type & 0x7f;
    switch (event_code) {
        case XCB_EXPOSE:
            // TODO: Resize window
            break;
        case XCB_CLIENT_MESSAGE:
            if ((*(xcb_client_message_event_t *)event).data.data32[0] == (*demo->atom_wm_delete_window).atom) {
                demo->quit = true;
            }
            break;
        case XCB_KEY_RELEASE: {
            const xcb_key_release_event_t *key = (const xcb_key_release_event_t *)event;

            switch (key->detail) {
                case 0x9:  // Escape
                    demo->quit = true;
                    break;
                case 0x71:  // left arrow key
                    demo->spin_angle -= demo->spin_increment;
                    break;
                case 0x72:  // right arrow key
                    demo->spin_angle += demo->spin_increment;
                    break;
                case 0x41:  // space bar
                    demo->pause = !demo->pause;
                    break;
            }
        } break;
        case XCB_CONFIGURE_NOTIFY: {
            const xcb_configure_notify_event_t *cfg = (const xcb_configure_notify_event_t *)event;
            if ((demo->width != cfg->width) || (demo->height != cfg->height)) {
                demo->width = cfg->width;
                demo->height = cfg->height;
                demo_resize(demo);
            }
        } break;
        default:
            break;
    }
}
}