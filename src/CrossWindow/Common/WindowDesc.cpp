#include "WindowDesc.h"

namespace xwin
{
  WindowDesc::WindowDesc()
  {
    visible = false;
    fullscreen = false;
    resizable = false;
    monitor = 0;

    title = "XWin";
    name = "XWinApp";
    iconPath = "";

    x = 0;
    y = 0;
    centered = true;

    width = 640;
    height = 360;
  }
}