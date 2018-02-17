#pragma once

#include <string>

/**
  * Initial window description
  */
namespace xwin
{
  struct WindowDesc
  {
    // States
    bool visible;
    bool fullscreen;
    bool resizable;
    unsigned monitor;
    // App Data
    std::string title;
    std::string name;
    std::string iconPath;
    // Transform
    unsigned x;
    unsigned y;
    unsigned width;
    unsigned height;

    WindowDesc();
  };


}