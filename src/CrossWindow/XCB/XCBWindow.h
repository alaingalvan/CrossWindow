#pragma once

#include "../Common/EventQueue.h"
#include "../Common/Init.h"
#include "../Common/WindowDesc.h"

#include <xcb/xcb.h>

namespace xwin
{
/**
 * XCB windows are pretty straight forward and easy, simple virtual function
 * calls:
 *
 * https://xcb.freedesktop.org/manual/group__XCB__Core__API.html
 */
class Window
{
  public:
    Window();

    // Initialize this window with the XCB API.
    bool create(const WindowDesc& desc, EventQueue& eventQueue);

    void close();

    xcb_connection_t* connection = nullptr;
    xcb_screen_t* screen = nullptr;
    xcb_window_t window = 0;
    unsigned display = 0;
};
}
