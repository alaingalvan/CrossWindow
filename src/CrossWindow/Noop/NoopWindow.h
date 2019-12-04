#pragma once

#include "../Common/EventQueue.h"
#include "../Common/Init.h"
#include "../Common/WindowDesc.h"

namespace xwin
{
class Window;

class NoopWindow
{
  public:
    ~NoopWindow();

    bool create(WindowDesc& desc, EventQueue& eventQueue, Window* parent);

    void showMouse(bool show);

    void setMousePosition(unsigned x, unsigned y);

    UVec2 getCurrentDisplaySize();

    void setWindowSize(unsigned x, unsigned y);

    void close();
};

typedef NoopWindow WindowDelegate;
}
