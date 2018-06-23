#include "../Common/Init.h"
#include "Main.h"

int main(int argc, char** argv)
{
    xwin::init(argc, argv);

        const xcb_setup_t *setup;
        xcb_screen_iterator_t iter;
        int scr;

        connection = xcb_connect(nullptr, &scr);
        if (xcb_connection_has_error(connection) > 0) {
            printf(
                "Cannot find a compatible Vulkan installable client driver "
                "(ICD).\nExiting ...\n");
            fflush(stdout);
            exit(1);
        }

        setup = xcb_get_setup(connection);
        iter = xcb_setup_roots_iterator(setup);
        while (scr-- > 0) xcb_screen_next(&iter);

        screen = iter.data;

    xmain(argc, argv);

    xcb_destroy_window(connection, xcb_window);
    xcb_disconnect(connection);
    free(atom_wm_delete_window);

    return 0;
}