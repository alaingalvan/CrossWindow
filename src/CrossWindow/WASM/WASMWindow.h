#pragma once

#include "../Common/EventQueue.h"
#include "../Common/Init.h"
#include "../Common/WindowDesc.h"

#include "emscripten/html5.h"

namespace xwin
{
class Window
{
  public:
    Window();

    bool create(WindowDesc& desc, EventQueue& eventQueue);

    WindowDesc getDesc();

    void close();

    WindowDesc mDesc;
};
}
