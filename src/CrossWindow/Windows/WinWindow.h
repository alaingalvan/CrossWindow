#pragma once


#include <Windows.h>
#include <unordered_map>
#include "../Common/WindowDesc.h"
#include "../CrossWindow.h"

namespace xwin
{
    class WinWindow
    {

        WinWindow(const WindowDesc& desc);

        bool create(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);

        static LRESULT CALLBACK WindowProcStatic(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

        LRESULT WindowProc(UINT msg, WPARAM wparam, LPARAM lparam);

    protected:
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

        static thread_local WinWindow* _windowBeingCreated;
        static thread_local std::unordered_map<HWND, WinWindow*> _hwndMap;
    };

    typedef WinWindow WindowDelegate;
}
