#pragma once

#include "../Common/WindowDesc.h"
#include "../Common/Init.h"
#include "../Common/EventQueue.h"

#include <unordered_map>
#include <Windows.h>


namespace xwin
{
    class Window;

    /**
     * Currently Win32Window uses the Win32 windowing protocol for the best backwards
     * compatibility possible. 
     * 
     * WinTouch is limited to the Windows 8 pointer API.
     * 
     * Events - https://msdn.microsoft.com/en-us/library/windows/desktop/ms644958%28v=vs.85%29.aspx?f=255&MSPPError=-2147217396
     * 
     */ 
    class Win32Window
    {
    public:
        Win32Window();

        ~Win32Window();

        bool create(WindowDesc& desc, EventQueue& eventQueue, Window* parent);

        void close();

        static LRESULT CALLBACK WindowProcStatic(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

        LRESULT WindowProc(UINT msg, WPARAM wparam, LPARAM lparam);

        // Application Handle
        HINSTANCE hinstance;

        // Window Handle
        HWND hwnd;

    protected:
        Window* mParent;

        EventQueue* mEventQueue;

        WindowDesc* mDesc;

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
