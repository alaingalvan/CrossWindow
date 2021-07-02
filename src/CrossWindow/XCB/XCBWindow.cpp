#include "XCBWindow.h"

namespace xwin
{
bool Window::create(WindowDesc& desc, EventQueue& eventQueue, Window* parent)
{
    const XWinState& xwinState = getXWinState();
    mConnection = xwinState.connection;

    uint32_t value_mask, value_list[32];

    mXcbWindowId = xcb_generate_id(mConnection);

    value_mask = XCB_CW_BACK_PIXEL | XCB_CW_EVENT_MASK;
    value_list[0] = mScreen->black_pixel;
    value_list[1] = XCB_EVENT_MASK_KEY_RELEASE | XCB_EVENT_MASK_EXPOSURE |
                    XCB_EVENT_MASK_STRUCTURE_NOTIFY;

    mDisplay = XOpenDisplay(NULL);
    mScreen = xcb_setup_roots_iterator(xcb_get_setup(mConnection)).data;

    xcb_create_window(mConnection, XCB_COPY_FROM_PARENT, mXcbWindowId,
                      mScreen->root, desc.x, desc.y, desc.width, desc.height, 0,
                      XCB_WINDOW_CLASS_INPUT_OUTPUT, mScreen->root_visual,
                      value_mask, value_list);

    xcb_map_window(mConnection, demo->xcb_window);

    const unsigned coords[] = {desc.x, desc.y};
    xcb_configure_window(mConnection, mXcbWindowId,
                         XCB_CONFIG_WINDOW_X | XCB_CONFIG_WINDOW_Y, coords);

    xcb_flush(mConnection);
}

}