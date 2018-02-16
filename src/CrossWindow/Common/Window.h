#pragma once

#include "WindowDesc.h"
#include "../Macros.h"

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

namespace xwin
{
    class Window
    {
    public:

        Window(const WindowDesc& desc);

        ~Window();

        bool eventLoop();

        void setTitle(char* title);

        void close();

        void minimize();

        void maximize();

        virtual void onResize();

        virtual void onKey();

        virtual void onMove();

        virtual void onTouch();

        virtual void onClose();

    protected:
        WindowDesc mDesc;
        WindowDelegate mDelegate;
    };
}