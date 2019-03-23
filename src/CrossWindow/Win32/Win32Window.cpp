#include "Win32Window.h"

namespace xwin
{
Win32Window::Win32Window() { hwnd = nullptr; };

Win32Window::~Win32Window()
{
    if (hwnd != nullptr)
    {
        close();
    }
}

bool Win32Window::create(WindowDesc& desc, EventQueue& eventQueue,
                         Window* parent)
{
    mParent = parent;
    mEventQueue = &eventQueue;
    const XWinState& xwinState = getXWinState();

    hinstance = xwinState.hInstance;
    HINSTANCE hPrevInstance = xwinState.hPrevInstance;
    LPSTR lpCmdLine = xwinState.lpCmdLine;
    int nCmdShow = xwinState.nCmdShow;

    mDesc = &desc;

    wndClass.cbSize = sizeof(WNDCLASSEX);
    wndClass.style = CS_HREDRAW | CS_VREDRAW;
    wndClass.lpfnWndProc = Win32Window::WindowProcStatic;
    wndClass.cbClsExtra = 0;
    wndClass.cbWndExtra = 0;
    wndClass.hInstance = hinstance;
    wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wndClass.lpszMenuName = NULL;
    wndClass.lpszClassName = mDesc->name.c_str();
    wndClass.hIconSm = LoadIcon(NULL, IDI_WINLOGO);

    if (!RegisterClassEx(&wndClass))
    {
        /**
         * Either an OS Error or a window with the same "name" id will cause
         * this to fail:
         */
        return false;
    }

    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);

    if (mDesc->fullscreen)
    {
        DEVMODE dmScreenSettings;
        memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
        dmScreenSettings.dmSize = sizeof(dmScreenSettings);
        dmScreenSettings.dmPelsWidth = screenWidth;
        dmScreenSettings.dmPelsHeight = screenHeight;
        dmScreenSettings.dmBitsPerPel = 32;
        dmScreenSettings.dmFields =
            DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

        if ((desc.width != screenWidth) && (desc.height != screenHeight))
        {
            if (ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN) !=
                DISP_CHANGE_SUCCESSFUL)
            {
                if (MessageBox(NULL,
                               "Fullscreen Mode not supported!\n Switch to "
                               "window mode?",
                               "Error", MB_YESNO | MB_ICONEXCLAMATION) == IDYES)
                {
                }
            }
        }
    }

    DWORD dwExStyle;
    DWORD dwStyle;

    if (mDesc->fullscreen)
    {
        dwExStyle = WS_EX_APPWINDOW;
        dwStyle = WS_POPUP | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;
    }
    else
    {
        dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
        dwStyle = WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;
    }

    RECT windowRect;
    windowRect.left = mDesc->x;
    windowRect.top = mDesc->y;
    windowRect.right = mDesc->fullscreen ? (long)screenWidth : (long)desc.width;
    windowRect.bottom =
        mDesc->fullscreen ? (long)screenHeight : (long)desc.height;

    AdjustWindowRectEx(&windowRect, dwStyle, FALSE, dwExStyle);

    _windowBeingCreated = this;
    hwnd = CreateWindowEx(0, mDesc->name.c_str(), mDesc->title.c_str(), dwStyle,
                          0, 0, windowRect.right - windowRect.left,
                          windowRect.bottom - windowRect.top, NULL, NULL,
                          hinstance, NULL);

    if (!hwnd)
    {
        printf("Could not create window!\n");
        fflush(stdout);
        exit(GetLastError());
    }

    if (!mDesc->fullscreen)
    {
        // Center on screen
        unsigned x = (GetSystemMetrics(SM_CXSCREEN) - windowRect.right) / 2;
        unsigned y = (GetSystemMetrics(SM_CYSCREEN) - windowRect.bottom) / 2;
        SetWindowPos(hwnd, 0, x, y, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
    }

    if (mDesc->visible)
    {
        ShowWindow(hwnd, SW_SHOW);
        SetForegroundWindow(hwnd);
        SetFocus(hwnd);
    }

    return true;
}

void Win32Window::updateDesc(WindowDesc& desc)
{
    windowRect.left = mDesc->x;
    windowRect.top = mDesc->y;
    windowRect.right = (long)desc.width;
    windowRect.bottom = (long)desc.height;

    AdjustWindowRectEx(&windowRect, dwStyle, FALSE, dwExStyle);

    SetWindowPos(hwnd, 0, desc.x, desc.y, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
}

void Win32Window::close()
{
    if (hwnd != nullptr)
    {
        DestroyWindow(hwnd);
        hwnd = nullptr;
    }
}

void Win32Window::showMouse(bool show) { ShowCursor(show ? TRUE : FALSE); }

void Win32Window::setTitle(std::string title)
{
    mDesc->title = title;
    SetWindowText(hwnd, mDesc->title.c_str());
}

void Win32Window::setPosition(unsigned x, unsigned y)
{
    SetWindowPos(hwnd, 0, x, y, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
    mDesc->x = x;
    mDesc->y = y;
}

void Win32Window::setWindowSize(unsigned width, unsigned height)
{
    windowRect.left = mDesc->x;
    windowRect.top = mDesc->y;
    windowRect.right = (long)width;
    windowRect.bottom = (long)height;

    AdjustWindowRectEx(&windowRect, dwStyle, FALSE, dwExStyle);
}

UVec2 Win32Window::getCurrentDisplaySize()
{
    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);
    UVec2 r;
    r.x = static_cast<unsigned>(screenWidth);
    r.y = static_cast<unsigned>(screenHeight);
    return r;
}

UVec2 Win32Window::getCurrentDisplayPosition()
{
    WINDOWPLACEMENT lpwndpl;
    UVec2 r;
    GetWindowPlacement(hwnd, &lpwndpl);
    r.x = lpwndpl.ptMinPosition.x;
    r.y = lpwndpl.ptMinPosition.y;
    return r;
}

void Win32Window::setMousePosition(unsigned x, unsigned y)
{
    SetCursorPos(x, y);
}

LRESULT CALLBACK Win32Window::WindowProcStatic(HWND hwnd, UINT msg,
                                               WPARAM wparam, LPARAM lparam)
{
    Win32Window* _this;
    if (_windowBeingCreated != nullptr)
    {
        _hwndMap.emplace(hwnd, _windowBeingCreated);
        _windowBeingCreated->hwnd = hwnd;
        _this = _windowBeingCreated;
        _windowBeingCreated = nullptr;
    }
    else
    {
        auto existing = _hwndMap.find(hwnd);
        _this = existing->second;
    }

    return _this->WindowProc(msg, wparam, lparam);
}

LRESULT Win32Window::WindowProc(UINT msg, WPARAM wparam, LPARAM lparam)
{
    MSG message;
    message.hwnd = hwnd;
    message.lParam = lparam;
    message.wParam = wparam;
    message.message = msg;
    message.time = 0;

    mEventQueue->getDelegate().pushEvent(message, mParent);

    return DefWindowProc(hwnd, msg, wparam, lparam);
}
}