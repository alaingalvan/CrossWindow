#pragma once

#include "../Common/WindowDesc.h"
#include "../Common/Init.h"
#include "../Common/EventQueue.h"

#include <unordered_map>
#include <Windows.h>


namespace xwin
{
    /**
     * Currently Win32Window uses the Win32 windowing protocol for the best backwards
     * compatibility possible. 
     * 
     * WinTouch is limited to the Windows 8 pointer api.
     * 
     * UWP Will probably be adopted as the default in the future 
     * for Xbox / Hololens support though. 
     * A flag XWIN_WINDOWS_PROTOCOL=AUTO will default to Win32 but can be UWP.
     * 
     * ~ ag
     */ 
    class Win32Window
    {
    public:
        Win32Window();

        ~Win32Window();

        bool create(WindowDesc& desc, EventQueue& eventQueue);

        static LRESULT CALLBACK WindowProcStatic(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

        LRESULT WindowProc(UINT msg, WPARAM wparam, LPARAM lparam);

    protected:
        WindowDesc* mDesc;

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

    };

    static thread_local Win32Window* _windowBeingCreated = nullptr;
    static thread_local std::unordered_map<HWND, Win32Window*> _hwndMap = {};

    typedef Win32Window WindowDelegate;
}
