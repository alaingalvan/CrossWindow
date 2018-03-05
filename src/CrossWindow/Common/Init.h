#pragma once

#include "State.h"

#ifdef XWIN_WINDOWS
#define MainArgs HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow
#define MainArgsVars hInstance, hPrevInstance, lpCmdLine, nCmdShow
#elif XWIN_ANDROID
#define MainArgs android_app* state
#define MainArgsVars state
#elif XWIN_LINUX || XWIN_MACOS || XWIN_IOS || XWIN_WASM
#define MainArgs int argc, const char* argv[]
#define MainArgsVars argc, argv
#endif

namespace xwin
{
    bool init(MainArgs);

    XWinState& getXWinState();
}
