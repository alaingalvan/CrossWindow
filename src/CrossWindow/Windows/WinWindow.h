#pragma once

// For now Win32 will be the default, later it'll be UMP
#define XWIN_WINDOWS_WIN32 0
#define XWIN_WINDOWS_UMP 1

#define XWIN_WINDOWS_PROTOCOL XWIN_WINDOWS_WIN32

#if XWIN_WINDOWS_PROTOCOL == XWIN_WINDOWS_WIN32
#include "Win32Window.h"
#elif XWIN_WINDOWS_PROTOCOL == XWIN_WINDOWS_UMP
#include "WinUMPWindow.h"
#endif