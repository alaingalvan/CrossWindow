#pragma once

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
    char* title;
    char* name;
    char* iconPath;
    // Transform
    unsigned x;
    unsigned y;
    unsigned width;
    unsigned height;

    WindowDesc();
  };


}