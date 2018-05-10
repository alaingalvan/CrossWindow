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

    android_app *state;

    XWinState(android_app *state) : state(state)
    {
    }
#elif defined(XWIN_MACOS) || defined(XWIN_IOS)

    int argc;
    const char **argv;
    void* nsApp;

    XWinState(int argc, const char **argv, void* nsApp) : argc(argc), argv(argv), nsApp(nsApp)
    {
    }

#else

    int argc;
    const char **argv;

    XWinState(int argc, const char **argv) : argc(argc), argv(argv)
    {
    }

#endif
    XWinState()
    {
    }
};
}