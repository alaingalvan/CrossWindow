#pragma once

#include "../Common/EventQueue.h"
#include "../Common/Init.h"
#include "../Common/WindowDesc.h"

#include <X11/Xlib.h>

typedef Window XLibWindow;

namespace xwin
{
class Window
{
  public:
    Window();

    bool create(const WindowDesc& desc, EventQueue& eventQueue);

    bool destroy();

  protected:
    Display* display = nullptr;
    XLibWindow window;
};
}
