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
};
}
