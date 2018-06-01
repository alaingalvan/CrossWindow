#pragma once

#include "State.h"

#if defined(XWIN_WINDOWS)
#define MainArgs HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow
#define MainArgsVars hInstance, hPrevInstance, lpCmdLine, nCmdShow
#elif defined(XWIN_ANDROID)
#define MainArgs android_app* app
#define MainArgsVars app
#elif defined(XWIN_MACOS) || defined(XWIN_IOS)
#define MainArgs int argc, const char* argv[], void* application
#define MainArgsVars argc, argv, application
#elif defined(XWIN_LINUX) || defined(XWIN_WASM) || defined(XWIN_NOOP)
#define MainArgs int argc, const char* argv[]
#define MainArgsVars argc, argv
#endif

namespace xwin
{
    bool init(MainArgs);

    const XWinState& getXWinState();
}
