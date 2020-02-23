#include "Win32Window.h"

#include "Shobjidl.h"
#include "dwmapi.h"
#include <windowsx.h>
#pragma comment(lib, "dwmapi.lib")
#pragma comment(lib, "uxtheme.lib")

enum Style : DWORD
{
    windowed = WS_OVERLAPPEDWINDOW,
    aero_borderless = WS_POPUP | WS_THICKFRAME,
    basic_borderless = WS_CAPTION | WS_OVERLAPPED | WS_THICKFRAME |
                       WS_MINIMIZEBOX | WS_MAXIMIZEBOX
};

HBRUSH hBrush = CreateSolidBrush(RGB(30, 30, 30));

namespace xwin
{
Window::Window() { hwnd = nullptr; };

Window::~Window()
{
    if (hwnd != nullptr)
    {
        close();
    }
}

const WindowDesc Window::getDesc() { return mDesc; }

bool Window::create(WindowDesc& desc, EventQueue& eventQueue)
{
    mEventQueue = &eventQueue;
    const XWinState& xwinState = getXWinState();

    hinstance = xwinState.hInstance;
    HINSTANCE hPrevInstance = xwinState.hPrevInstance;
    LPSTR lpCmdLine = xwinState.lpCmdLine;
    int nCmdShow = xwinState.nCmdShow;

    mDesc = desc;

    wndClass.cbSize = sizeof(WNDCLASSEX);
    wndClass.style = CS_HREDRAW | CS_VREDRAW;
    wndClass.lpfnWndProc = Window::WindowProcStatic;
    wndClass.cbClsExtra = 0;
    wndClass.cbWndExtra = WS_EX_NOPARENTNOTIFY;
    wndClass.hInstance = hinstance;
    wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndClass.hbrBackground = hBrush;
    wndClass.lpszMenuName = NULL;
    wndClass.lpszClassName = mDesc.name.c_str();
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

    if (mDesc.fullscreen)
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

    DWORD dwExStyle = 0;
    DWORD dwStyle = 0;

    if (mDesc.fullscreen)
    {
        dwExStyle = WS_EX_APPWINDOW;
        dwStyle = WS_POPUP | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;
    }
    else
    {
        dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
        // dwExStyle &=
        //    ~(WS_EX_DLGMODALFRAME | WS_EX_CLIENTEDGE | WS_EX_STATICEDGE);
        dwStyle = Style::basic_borderless;
    }

    RECT windowRect;
    windowRect.left = mDesc.x;
    windowRect.top = mDesc.y;
    windowRect.right = mDesc.fullscreen ? (long)screenWidth : (long)desc.width;
    windowRect.bottom =
        mDesc.fullscreen ? (long)screenHeight : (long)desc.height;

    AdjustWindowRectEx(&windowRect, dwStyle, FALSE, dwExStyle);

    _windowBeingCreated = this;
    hwnd = CreateWindowEx(0, mDesc.name.c_str(), mDesc.title.c_str(), dwStyle,
                          0, 0, windowRect.right - windowRect.left,
                          windowRect.bottom - windowRect.top, NULL, NULL,
                          hinstance, NULL);

    BOOL isNCRenderingEnabled{TRUE};
    DwmSetWindowAttribute(hwnd, DWMWA_NCRENDERING_ENABLED,
                          &isNCRenderingEnabled, sizeof(isNCRenderingEnabled));

    if (!hwnd)
    {
        // Failed to create window...
        return false;
    }

    if (!mDesc.fullscreen)
    {
        // Center on screen
        unsigned x = (GetSystemMetrics(SM_CXSCREEN) - windowRect.right) / 2;
        unsigned y = (GetSystemMetrics(SM_CYSCREEN) - windowRect.bottom) / 2;
        SetWindowPos(hwnd, 0, x, y, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
    }

    if (mDesc.visible)
    {
        ShowWindow(hwnd, SW_SHOW);
        SetForegroundWindow(hwnd);
        SetFocus(hwnd);
    }

    static const DWM_BLURBEHIND blurBehind{{0}, {TRUE}, {NULL}, {TRUE}};
    DwmEnableBlurBehindWindow(hwnd, &blurBehind);
    static const MARGINS shadow_state[2]{{0, 0, 0, 0}, {1, 1, 1, 1}};
    ::DwmExtendFrameIntoClientArea(hwnd, &shadow_state[0]);

    RegisterWindowMessage("TaskbarButtonCreated");
    HRESULT hrf =
        CoCreateInstance(CLSID_TaskbarList, NULL, CLSCTX_INPROC_SERVER,
                         IID_ITaskbarList3, (LPVOID*)&mTaskbarList);
    setProgress(0.0f);

    // FlashWindow(hwnd, true);
    // MoveWindow(hwnd, 0, 0, desc.width,
    //           desc.height + 8, true);

    return true;
}

void Window::updateDesc(WindowDesc& desc)
{
    windowRect.left = mDesc.x;
    windowRect.top = mDesc.y;
    windowRect.right = (long)desc.width;
    windowRect.bottom = (long)desc.height;

    AdjustWindowRectEx(&windowRect, dwStyle, FALSE, dwExStyle);

    SetWindowPos(hwnd, 0, desc.x, desc.y, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
}

void Window::close()
{
    if (hwnd != nullptr)
    {
        DestroyWindow(hwnd);
        hwnd = nullptr;
    }
}

void Window::setProgress(float progress)
{
    unsigned max = 10000;
    unsigned cur = (unsigned)(progress * (float)max);
    mTaskbarList->SetProgressValue(hwnd, cur, max);
}

void Window::showMouse(bool show) { ShowCursor(show ? TRUE : FALSE); }

std::string Window::getTitle() const
{
    char str[1024];
    memset(str, 0, sizeof(char) * 1024);
    GetWindowTextA(hwnd, str, 1024);
    std::string outStr = std::string(str);
    return outStr;
}

void Window::setTitle(std::string title)
{
    mDesc.title = title;
    SetWindowText(hwnd, mDesc.title.c_str());
}

void Window::setPosition(unsigned x, unsigned y)
{
    SetWindowPos(hwnd, 0, x, y, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
    mDesc.x = x;
    mDesc.y = y;
}

void Window::setSize(unsigned width, unsigned height)
{
    RECT lpRect;
    if (GetWindowRect(hwnd, &lpRect))
    {
        SetWindowPos(hwnd, nullptr, lpRect.left, lpRect.top, width, height, 0);
        mDesc.x = lpRect.left;
        mDesc.y = lpRect.top;
        mDesc.width = width;
        mDesc.height = height;
    }
}

UVec2 Window::getPosition() const
{
    RECT lpRect;
    GetWindowRect(hwnd, &lpRect);
    return UVec2(lpRect.left, lpRect.top);
}

UVec2 Window::getWindowSize() const
{
    RECT lpRect;
    GetWindowRect(hwnd, &lpRect);
    return UVec2(lpRect.right - lpRect.left, lpRect.bottom - lpRect.top);
}

UVec2 Window::getCurrentDisplaySize() const
{
    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);
    UVec2 r = UVec2(static_cast<unsigned>(screenWidth),
                    static_cast<unsigned>(screenHeight));
    return r;
}

UVec2 Window::getCurrentDisplayPosition() const
{
    WINDOWPLACEMENT lpwndpl;
    GetWindowPlacement(hwnd, &lpwndpl);
    UVec2 r = UVec2(lpwndpl.ptMinPosition.x, lpwndpl.ptMinPosition.y);
    return r;
}

void Window::setMousePosition(unsigned x, unsigned y) { SetCursorPos(x, y); }

void Window::executeEventCallback(const xwin::Event e)
{
    if (mCallback) mCallback(e);
}

LRESULT CALLBACK Window::WindowProcStatic(HWND hwnd, UINT msg, WPARAM wparam,
                                          LPARAM lparam)
{
    Window* _this;
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

LRESULT Window::WindowProc(UINT msg, WPARAM wparam, LPARAM lparam)
{
    MSG message;
    message.hwnd = hwnd;
    message.lParam = lparam;
    message.wParam = wparam;
    message.message = msg;
    message.time = 0;

    LRESULT result = mEventQueue->pushEvent(message, this);
    if (result > 0) return result;
    return DefWindowProc(hwnd, msg, wparam, lparam);
}
}