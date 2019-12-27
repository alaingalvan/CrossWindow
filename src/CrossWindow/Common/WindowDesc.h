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
    long x;
    long y;
    bool centered;
    unsigned width;
    unsigned height;

    WindowDesc();
};

struct UVec2
{
    unsigned x;
    unsigned y;
    UVec2(unsigned x = 0, unsigned y = 0) : x(x), y(y) {}
};
}
