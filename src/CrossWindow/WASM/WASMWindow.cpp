#include "WASMWindow.h"

namespace xwin
{
Window::Window() {}

bool Window::create(WindowDesc& desc, EventQueue& eventQueue)
{
    mDesc = desc;

    EM_ASM(var canvas = document.createElement('canvas');
           document.body.appendChild(canvas); canvas.id = 'MainWindow';);

    emscripten_set_canvas_element_size(desc.name.c_str(), desc.width,
                                       desc.height);
    return true;
}

void Window::close()
{
    EM_ASM(var canvas = document.getElementById('MainWindow');
           document.body.removeChild(canvas););
}

WindowDesc Window::getDesc() { return mDesc; }
}