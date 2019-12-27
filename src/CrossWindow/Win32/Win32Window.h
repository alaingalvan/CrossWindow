#pragma once

#include "../Common/EventQueue.h"
#include "../Common/Init.h"
#include "../Common/WindowDesc.h"

#include <Windows.h>
#include <unordered_map>

#include <functional>

class ITaskbarList3;

namespace xwin
{
class Window;

/**
 * Currently Win32Window uses the Win32 windowing protocol for the best
 * backwards compatibility possible.
 *
 * WinTouch is limited to the Windows 8 pointer API.
 *
 * Events -
 * https://msdn.microsoft.com/en-us/library/windows/desktop/ms644958%28v=vs.85%29.aspx?f=255&MSPPError=-2147217396
 *
 */
class Window
{
  public:
    Window();

    ~Window();

    bool create(WindowDesc& desc, EventQueue& eventQueue);

    const WindowDesc getDesc();

    void updateDesc(WindowDesc& desc);

    void Window::setTitle(std::string title);

    void Window::setPosition(unsigned x, unsigned y);

    void Window::setMousePosition(unsigned x, unsigned y);

    void Window::showMouse(bool show);

    void Window::setWindowSize(unsigned width, unsigned height);

    void Window::setProgress(float progress);

    UVec2 Window::getCurrentDisplaySize();

    // returns the current top left corner this window is located in
    UVec2 Window::getCurrentDisplayPosition();

    // UVec2 Window::getWindowSize();

    // std::string Window::getTitle();

    void close();

    // Executes an event callback asynchronously, use this for non-blocking
    // events (resizing while rendering, etc.)
    void executeEventCallback(const xwin::Event e);

    static LRESULT CALLBACK WindowProcStatic(HWND hwnd, UINT msg, WPARAM wparam,
                                             LPARAM lparam);

    LRESULT WindowProc(UINT msg, WPARAM wparam, LPARAM lparam);

    // Application Handle
    HINSTANCE hinstance;

    // Window Handle
    HWND hwnd;

    std::function<void(const xwin::Event e)> mCallback;

  protected:
    EventQueue* mEventQueue;

    WindowDesc mDesc;

    // Window State
    WNDCLASSEX wndClass;

    // Window Size/Position
    RECT windowRect;

    // Screen State
    DEVMODE dmScreenSettings;

    // Window Behavior
    DWORD dwExStyle;
    DWORD dwStyle;

    // Taskbar Interface
    ITaskbarList3* mTaskbarList;
};

static thread_local Window* _windowBeingCreated = nullptr;
static thread_local std::unordered_map<HWND, Window*> _hwndMap = {};

typedef Window WindowDelegate;
}
