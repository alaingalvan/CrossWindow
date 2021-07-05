#include "../Common/Init.h"
#include "Main.h"

#include <xcb/xcb.h>

int main(int argc, const char** argv)
{
    int screenNum = 0;
    xcb_connection_t* connection = xcb_connect(nullptr, &screenNum);

    if (xcb_connection_has_error(connection) > 0)
    {
        return 1;
    }

    /* Get the screen whose number is screenNum */

    const xcb_setup_t* setup = xcb_get_setup(connection);
    xcb_screen_iterator_t iter = xcb_setup_roots_iterator(setup);

    // we want the screen at index screenNum of the iterator
    for (int i = 0; i < screenNum; ++i)
    {
        xcb_screen_next(&iter);
    }

    xcb_screen_t* screen = iter.data;

    xwin::init(argc, argv, connection, screen);

    xmain(argc, argv);

    xcb_disconnect(connection);

    return 0;
}