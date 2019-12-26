#pragma once

#include <string>

#include "../Common/WindowDesc.h"

namespace xwin
{
class Window
{
    bool create(const WindowDesc& desc, EventQueue& queue);

    void close();

    void setTitle(std::string title);
};
}