#pragma once

#include "WindowDesc.h"

#include "EventQueue.h"

#ifdef XWIN_WINDOWS
#include "../Windows/WinWindow.h"
#elif XWIN_MACOS
#include "../MacOS/MacOSWindow.h"
#elif XWIN_LINUX
#include "../Linux/LinuxWindow.h"
#elif XWIN_ANDROID
#include "../Android/AndroidWindow.h"
#elif XWIN_IOS
#include "../iOS/iOSWindow.h"
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

        WindowDesc getDesc() const;

        WindowDelegate& getDelegate();

    protected:
        WindowDesc mDesc;
        WindowDelegate mDelegate;
    };

    typedef std::shared_ptr<Window> WindowPtr;
}