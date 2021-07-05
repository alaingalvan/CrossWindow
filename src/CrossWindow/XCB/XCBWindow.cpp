#include "XCBWindow.h"

namespace xwin
{
Window::Window() {}

bool Window::create(const WindowDesc& desc, EventQueue& eventQueue)
{
    const XWinState& xwinState = getXWinState();
    mConnection = xwinState.connection;
    mScreen = xwinState.screen;

    mXcbWindowId = xcb_generate_id(mConnection);

    uint32_t mask = XCB_CW_BACK_PIXEL | XCB_CW_EVENT_MASK;
    uint32_t value_list[2] = {
        mScreen->black_pixel,
        XCB_EVENT_MASK_EXPOSURE | XCB_EVENT_MASK_BUTTON_PRESS |
            XCB_EVENT_MASK_BUTTON_RELEASE | XCB_EVENT_MASK_POINTER_MOTION |
            XCB_EVENT_MASK_ENTER_WINDOW | XCB_EVENT_MASK_LEAVE_WINDOW |
            XCB_EVENT_MASK_KEY_PRESS | XCB_EVENT_MASK_KEY_RELEASE};

    xcb_create_window(mConnection, XCB_COPY_FROM_PARENT, mXcbWindowId,
                      mScreen->root, desc.x, desc.y, desc.width, desc.height, 0,
                      XCB_WINDOW_CLASS_INPUT_OUTPUT, mScreen->root_visual, mask,
                      value_list);

    xcb_map_window(mConnection, mXcbWindowId);

    const unsigned coords[] = {static_cast<unsigned>(desc.x),
                               static_cast<unsigned>(desc.y)};
    xcb_configure_window(mConnection, mXcbWindowId,
                         XCB_CONFIG_WINDOW_X | XCB_CONFIG_WINDOW_Y, coords);

    xcb_flush(mConnection);

    return true;
}

void Window::close() { xcb_destroy_window(mConnection, mXcbWindowId); }

}