#pragma once

#if defined(XWIN_WINDOWS)
#include <Windows.h>
#endif

namespace xwin
{
struct XWinState
{

#ifdef XWIN_WINDOWS

    HINSTANCE hInstance;
    HINSTANCE hPrevInstance;
    LPSTR lpCmdLine;
    int nCmdShow;

    XWinState(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) : hInstance(hInstance), hPrevInstance(hPrevInstance), lpCmdLine(lpCmdLine), nCmdShow(nCmdShow)
    {
    }

#elif XWIN_ANDROID

    android_app *app;

    XWinState(android_app *app) : app(app)
    {
    }
#elif defined(XWIN_MACOS) || defined(XWIN_IOS)

    int argc;
    const char** argv;
    void* application;

    XWinState(int argc, const char **argv, void* application) : argc(argc), argv(argv), application(application)
    {
    }

#else

    int argc;
    const char** argv;

    XWinState(int argc, const char **argv) : argc(argc), argv(argv)
    {
    }

#endif
    XWinState()
    {
    }
};
}
