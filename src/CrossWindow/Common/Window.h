#pragma once

#include "WindowDesc.h"

#include "EventQueue.h"

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
#elif XWIN_MIR
#include "../Mir/MirWindow.h"
#elif XWIN_WAYLAND
#include "../Wayland/WaylandWindow.h"
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

    class Window
    {
    public:

        Window();

        ~Window();

        /**
         * Initialize the OS specific data structures needed to create a window.
         * Pass a description of your window, as well as an event queue to listen to events from that window.
         */ 
        bool create(const WindowDesc& desc, EventQueue& queue);

        void showMouse(bool show);

        void setMousePosition(unsigned x, unsigned y);

        UVec2 getCurrentDisplaySize();

        /**
         * Destroy this window.
         */
        void close();

        WindowDesc getDesc() const;

        WindowDelegate& getDelegate();

    protected:
        WindowDesc mDesc;
        WindowDelegate mDelegate;
    };

    typedef std::shared_ptr<Window> WindowPtr;
}