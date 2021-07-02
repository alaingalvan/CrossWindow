#pragma once

#ifdef __linux__
#ifndef __ANDROID__
#include <xcb/xcb.h>
#endif
#endif

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
    XCBWindow();

    // Initialize this window with the XCB API.
    bool create(const WindowDesc& desc, EventQueue& eventQueue);

  protected:
    xcb_connection_t mConnection = 0;
    xcb_screen_t* mScreen = nullptr;
	unsigned mXcbWindowId = 0;
    unsigned mDisplay = 0;
    
};
}
