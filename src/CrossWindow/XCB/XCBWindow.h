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

  protected:
    xcb_connection_t* mConnection = nullptr;
    xcb_screen_t* mScreen = nullptr;
    unsigned mXcbWindowId = 0;
    unsigned mDisplay = 0;
};
}
