#pragma once

#include "WindowDesc.h"

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

        bool create(const WindowDesc& desc);

        std::vector<EventType>& pollEvents();

        void close();

    protected:
        WindowDesc mDesc;
        WindowDelegate mDelegate;
    };

    typedef std::shared_ptr<Window> WindowPtr;
}