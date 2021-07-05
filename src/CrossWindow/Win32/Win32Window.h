#pragma once

#include "../Common/EventQueue.h"
#include "../Common/Init.h"
#include "../Common/WindowDesc.h"

#include <Windows.h>
#include <unordered_map>

#include <functional>

struct ITaskbarList3;

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

namespace xwin
{

class Window
{
  public:
    Window();

    ~Window();

    // Initialize this window with the Win32 API.
    bool create(const WindowDesc& desc, EventQueue& eventQueue);

    // Get this Window's descriptor object.
    const WindowDesc getDesc();

    // Update the window descriptor. Useful for batch updates.
    void updateDesc(WindowDesc& desc);

    // Set the title of this window.
    void setTitle(std::string title);

    // Set the position of this window based on the top left corner.
    void setPosition(unsigned x, unsigned y);

    // Set the mouse position in display space.
    void setMousePosition(unsigned x, unsigned y);

    // Show or hide the mouse cursor.
    void showMouse(bool show);

    void setSize(unsigned width, unsigned height);

    // Set progress visible in the taskbar
    void setProgress(float progress);

    // Get the position of this window in display space.
    UVec2 getPosition() const;

    // Get the size of the current display this window is in.
    UVec2 getCurrentDisplaySize() const;

    // returns the current top left corner this window is located in
    UVec2 getCurrentDisplayPosition() const;

    // Get this window's size in pixels.
    UVec2 getWindowSize() const;

    // Get the title of this window.
    std::string getTitle() const;

    // Request that this window be closed.
    void close();

    // Track events asynchronously for this window
    void trackEventsAsync(const std::function<void(const xwin::Event e)>& fun);

    // Windows Only Functions:

    // Get this window's application Handle.
    HINSTANCE getHinstance();

    // Get this window hwnd handle.
    HWND getHwnd();

    friend class EventQueue;

  protected:
    // Executes an event callback asynchronously, use this for non-blocking
    // events (resizing while rendering, etc.)
    void executeEventCallback(const xwin::Event e);

    std::function<void(const xwin::Event e)> mCallback;

    static LRESULT CALLBACK WindowProcStatic(HWND hwnd, UINT msg, WPARAM wparam,
                                             LPARAM lparam);

    LRESULT WindowProc(UINT msg, WPARAM wparam, LPARAM lparam);

    HWND hwnd;

    HINSTANCE hinstance;

    // Pointer to this window's event queue
    EventQueue* mEventQueue;

    // CrossWindow's descriptor object
    WindowDesc mDesc;

    // Win32 Window State
    WNDCLASSEX wndClass;

    // Win32 Window Size/Position
    RECT windowRect;

    // Win32 Screen State
    DEVMODE dmScreenSettings;

    // Win32 Window Behavior
    DWORD dwExStyle;
    DWORD dwStyle;

    // Win32 Taskbar Interface
    ITaskbarList3* mTaskbarList;
};

static thread_local Window* _windowBeingCreated = nullptr;
static thread_local std::unordered_map<HWND, Window*> _hwndMap = {};
}
