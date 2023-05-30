#include "WASMWindow.h"

namespace xwin
{
Window::Window() {}

bool Window::create(WindowDesc& desc, EventQueue& eventQueue)
{
    mDesc = desc;

    EM_ASM(
        if(! document.getElementById('canvas'))
        {
            var canvas = document.createElement('canvas');
            document.body.appendChild(canvas);
            canvas.id = 'canvas';
            canvas.className = 'emscripten';
        }
    );

    emscripten_set_canvas_element_size("canvas", desc.width, desc.height);
    return true;
}

void Window::close()
{
    EM_ASM(
        var canvas = document.getElementById('canvas');
        document.body.removeChild(canvas);
    );
}

WindowDesc Window::getDesc() { return mDesc; }
}
