#pragma once

#ifdef XWIN_WIN32
#include "../Win32/Win32Window.h"
#elif XWIN_UWP
#include "../UWP/UWPWindow.h"
#elif XWIN_COCOA
#include "../Cocoa/CocoaWindow.h"
#elif XWIN_XCB
#include "../XCB/XCBWindow.h"
#elif XWIN_XLIB
#include "../XLib/XLibWindow.h"
#elif XWIN_ANDROID
#include "../Android/AndroidWindow.h"
#elif XWIN_UIKIT
#include "../UIKit/UIKitWindow.h"
#elif XWIN_WASM
#include "../WASM/WASMWindow.h"
#elif XWIN_NOOP
#include "../Noop/NoopWindow.h"
#endif

#include <memory>

namespace xwin
{
typedef std::shared_ptr<Window> WindowPtr;
typedef std::weak_ptr<Window> WindowWeakPtr;
}