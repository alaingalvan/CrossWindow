#include "WindowDesc.h"

namespace mwin
{
  WindowDesc::WindowDesc()
  {
    visible = true;
    fullscreen = true;
    resizable = false;
    monitor = 0;

    title = "";
    name = "";
    iconPath = "";

    x = 0;
    y = 0;
    width = 0;
    height = 0;
  }
}