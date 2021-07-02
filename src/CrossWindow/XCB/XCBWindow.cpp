#include "XCBWindow.h"

namespace xwin
{
bool Window::create(const WindowDesc& desc, EventQueue& eventQueue)
{
    const XWinState& xwinState = getXWinState();
    mConnection = xwinState.connection;
    mScreen = xwinState.screen;

    uint32_t value_mask, value_list[32];

    mXcbWindowId = xcb_generate_id(mConnection);

    value_mask = XCB_CW_BACK_PIXEL | XCB_CW_EVENT_MASK;
    value_list[0] = mScreen->black_pixel;
    value_list[1] = XCB_EVENT_MASK_KEY_RELEASE | XCB_EVENT_MASK_EXPOSURE |
                    XCB_EVENT_MASK_STRUCTURE_NOTIFY;

    xcb_create_window(mConnection, XCB_COPY_FROM_PARENT, mXcbWindowId,
                      mScreen->root, desc.x, desc.y, desc.width, desc.height, 0,
                      XCB_WINDOW_CLASS_INPUT_OUTPUT, mScreen->root_visual,
                      value_mask, value_list);

    xcb_map_window(mConnection, mXcbWindowId);

    const unsigned coords[] = {desc.x, desc.y};
    xcb_configure_window(mConnection, mXcbWindowId,
                         XCB_CONFIG_WINDOW_X | XCB_CONFIG_WINDOW_Y, coords);

    xcb_flush(mConnection);
}

void Window::close() { xcb_destroy_window(mConnection, mXcbWindowId); }

}