#pragma once

#if XWIN_WINDOWS_PROTOCOL == XWIN_WINDOWS_UMP
#include "WinUMPEventQueue.h"
#else
#include "Win32EventQueue.h"
#endif