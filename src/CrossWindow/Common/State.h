#pragma once

#if defined(XWIN_WIN32)
#include <Windows.h>
#elif defined(XWIN_XCB)
#include <xcb/xcb.h>
#elif defined(XWIN_XLIB)
#include <X11/Xlib.h>
#endif

namespace xwin
{
struct XWinState
{

#if defined(XWIN_WIN32)

    HINSTANCE hInstance;
    HINSTANCE hPrevInstance;
    LPSTR lpCmdLine;
    int nCmdShow;

    XWinState(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine,
              int nCmdShow)
        : hInstance(hInstance), hPrevInstance(hPrevInstance),
          lpCmdLine(lpCmdLine), nCmdShow(nCmdShow)
    {
    }
#elif defined(XWIN_COCOA) || defined(XWIN_UIKIT)

    int argc;
    const char** argv;
    void* application;

    XWinState(int argc, const char** argv, void* application)
        : argc(argc), argv(argv), application(application)
    {
    }
#elif defined(XWIN_XCB)
    int argc;
    const char** argv;
    xcb_connection_t* connection;
    xcb_screen_t* screen;
    XWinState(int argc, const char** argv, xcb_connection_t* connection,
              xcb_screen_t* screen)
        : argc(argc), argv(argv), connection(connection), screen(screen)
    {
    }

#elif defined(XWIN_ANDROID)

    android_app* app;

    XWinState(android_app* app) : app(app) {}

#else

    int argc;
    const char** argv;

    XWinState(int argc, const char** argv) : argc(argc), argv(argv) {}

#endif
    XWinState() {}
};
}
