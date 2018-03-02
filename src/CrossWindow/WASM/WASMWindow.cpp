#include "WASMWindow.h"

namespace xwin
{
    WASMWindow::WASMWindow()
    {
        // void emscripten_set_main_loop(em_callback_func func, int fps, int simulate_infinite_loop);
        emscripten_set_main_loop(one_iter, 60, 1);
    }
}