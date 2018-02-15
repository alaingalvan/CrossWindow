#pragma once

#include "WindowDesc.h"
#include "../Macros.h"

#ifdef MAG_NOOP
#include "noop/nodevice.h"
#elif WIN32
#ifdef MAG_DX
#include "directx/dxdevice.h"
#elif MAG_OGL
#include "OpenGL/gldevice.h"
#else
#include "../vulkan/vkdevice.h"
#endif
#elif __APPLE__
#if MAG_OGL
#include "../OpenGL/ogldevice.h"
#else
#include "metal/mtdevice.h"
#endif
#endif

namespace mwin
{
  class Window
  {
  public:
    
    Window(const WindowDesc& desc);

    ~Window();
    
    mag::Surface getSurface(mag::Instance &instance);

    bool eventLoop();

    void setTitle(char* title);

    void close();

    void minimize();

    void maximize();

    virtual void onResize();

    virtual void onKey();

    virtual void onMove();

    virtual void onTouch();

    virtual void onClose();

  private:
    WindowDesc desc;
    WindowDelegate delegate;
  };
}