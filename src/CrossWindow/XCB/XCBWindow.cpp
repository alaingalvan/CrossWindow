#include "XCBWindow.h"

namespace xwin
{
  bool XCBWindow::create(WindowDesc& desc, EventQueue& eventQueue, Window* parent)
  {
    const XWinState& xwinState = getXWinState();
    mConnection = xwinState.connection;

    uint32_t value_mask, value_list[32];

    mxcb_window = xcb_generate_id(mConnection);

    value_mask = XCB_CW_BACK_PIXEL | XCB_CW_EVENT_MASK;
    value_list[0] = mScreen->black_pixel;
    value_list[1] = XCB_EVENT_MASK_KEY_RELEASE | XCB_EVENT_MASK_EXPOSURE | XCB_EVENT_MASK_STRUCTURE_NOTIFY;

    xcb_create_window(mConnection, XCB_COPY_FROM_PARENT, demo->xcb_window, demo->screen->root, 0, 0, demo->width, demo->height,
                      0, XCB_WINDOW_CLASS_INPUT_OUTPUT, demo->screen->root_visual, value_mask, value_list);

    /* Magic code that will send notification when window is destroyed */
    xcb_intern_atom_cookie_t cookie = xcb_intern_atom(demo->connection, 1, 12, "WM_PROTOCOLS");
    xcb_intern_atom_reply_t *reply = xcb_intern_atom_reply(demo->connection, cookie, 0);

    xcb_intern_atom_cookie_t cookie2 = xcb_intern_atom(demo->connection, 0, 16, "WM_DELETE_WINDOW");
    demo->atom_wm_delete_window = xcb_intern_atom_reply(demo->connection, cookie2, 0);

    xcb_change_property(mConnection, XCB_PROP_MODE_REPLACE, demo->xcb_window, (*reply).atom, 4, 32, 1,
                        &(*demo->atom_wm_delete_window).atom);
    free(reply);

    xcb_map_window(demo->connection, demo->xcb_window);

    // Force the x/y coordinates to 100,100 results are identical in consecutive
    // runs
    const uint32_t coords[] = {100, 100};
    xcb_configure_window(demo->connection, demo->xcb_window, XCB_CONFIG_WINDOW_X | XCB_CONFIG_WINDOW_Y, coords);

        xcb_flush(demo->connection);
  }


}