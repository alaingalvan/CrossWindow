#pragma once

#include "../Common/WindowDesc.h"
#include "../Common/Init.h"

#include <unordered_map>
#include <Windows.h>


namespace xwin
{
    class WinWindow
    {
    public:
        WinWindow();

        bool create(WindowDesc& desc);

        bool eventLoop();

        std::vector<EventType>& pollEvents();

        bool close();

        static LRESULT CALLBACK WindowProcStatic(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

        LRESULT WindowProc(UINT msg, WPARAM wparam, LPARAM lparam);

    protected:
        WindowDesc* mDesc;

        bool mCloseWindow;

        // Application Handle
        HINSTANCE hInstance;

        // Window Handle
        HWND _hwnd;

        // Window State
        WNDCLASSEX wndClass;

        // Window Size/Position
        RECT windowRect;

        // Screen State
        DEVMODE dmScreenSettings;

        // Window Behavior
        DWORD dwExStyle;
        DWORD dwStyle;

        std::vector<EventType> mEventQueue;

    };

    static thread_local WinWindow* _windowBeingCreated = nullptr;
    static thread_local std::unordered_map<HWND, WinWindow*> _hwndMap = {};

    typedef WinWindow WindowDelegate;
}
