#pragma once

#include <vector>

#include "Event.h"

#ifdef XWIN_WINDOWS
#include "../Windows/WinEventQueue.h"
#elif XWIN_MACOS
#include "../MacOS/MacOSEventQueue.h"
#elif XWIN_LINUX
#include "../Linux/LinuxEventQueue.h"
#elif XWIN_ANDROID
#include "../Android/AndroidEventQueue.h"
#elif XWIN_IOS
#include "../iOS/iOSEventQueue.h"
#elif XWIN_WASM
#include "../WASM/WASMEventQueue.h"
#elif XWIN_NOOP
#include "../Noop/NoopEventQueue.h"
#endif

namespace xwin
{
    class Window;

    class EventQueue
    {
        public:
        EventQueue();

        bool update();

        const Event& front();

        void pop();

        protected:
            std::vector<Window*> windows;

            EventQueueDelegate mDelegate;
    };
}