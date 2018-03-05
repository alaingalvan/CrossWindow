#pragma once

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