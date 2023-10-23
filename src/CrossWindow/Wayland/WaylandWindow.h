#pragma once

#include "../Common/EventQueue.h"
#include "../Common/Init.h"
#include "../Common/WindowDesc.h"

namespace xwin
{
class Window
{
  public:
    Window();
    ~Window();

    // Initialize this window with the XCB API.
    bool create(const WindowDesc& desc, EventQueue& eventQueue);

    void close();

    // Request that this window be minimized.
    void minimize();

    // Request that this window be maximized.
    void maximize();

    // Set callback func
    void trackEventsAsync(const std::function<void(const xwin::Event e)>& fun);

    // Get window description
    const WindowDesc getDesc();

  protected:
    // Pointer to this window's event queue
    EventQueue* mEventQueue = nullptr;

    // Executes an event callback asynchronously, use this for non-blocking
    // events (resizing while rendering, etc.)
    void executeEventCallback(const xwin::Event e);

    std::function<void(const xwin::Event e)> mCallback;

    // Window description
    WindowDesc mDesc;

  public:
};
}
