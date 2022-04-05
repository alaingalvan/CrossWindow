#pragma once

#include "../Common/EventQueue.h"
#include "../Common/Init.h"
#include "../Common/WindowDesc.h"

namespace xwin
{
class Window;

class Window
{
  public:
    ~Window();

    bool create(const WindowDesc& desc, EventQueue& eventQueue);

    void close();

    const WindowDesc getDesc();

    void updateDesc(WindowDesc& desc);

    void setTitle(std::string title);

    void setPosition(unsigned x, unsigned y);

    void setMousePosition(unsigned x, unsigned y);

    void showMouse(bool show);

    void setSize(unsigned width, unsigned height);

    void setProgress(float progress);

    UVec2 getCurrentDisplaySize();

    // returns the current top left corner this window is located in
    UVec2 getCurrentDisplayPosition();

  protected:
    WindowDesc mDesc;
};
}
