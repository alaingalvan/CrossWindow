#include "../Common/Init.h"
#include "Main.h"

int main(int argc, char** argv)
{
    xwin::init(argc, argv);

    

    xmain(argc, argv);

    XDestroyWindow(display, xlib_window);
    XCloseDisplay(display);

    return 0;
}