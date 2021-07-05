#pragma once

#include <vector>

#include "Event.h"

#ifdef XWIN_WIN32
#include "../Win32/Win32EventQueue.h"
#elif XWIN_UWP
#include "../UWP/UWPEventQueue.h"
#elif XWIN_COCOA
#include "../Cocoa/CocoaEventQueue.h"
#elif XWIN_XCB
#include "../XCB/XCBEventQueue.h"
#elif XWIN_XLIB
#include "../XLib/XLibEventQueue.h"
#elif XWIN_ANDROID
#include "../Android/AndroidEventQueue.h"
#elif XWIN_UIKIT
#include "../UIKit/UIKitEventQueue.h"
#elif XWIN_WASM
#include "../WASM/WASMEventQueue.h"
#elif XWIN_NOOP
#include "../Noop/NoopEventQueue.h"
#endif