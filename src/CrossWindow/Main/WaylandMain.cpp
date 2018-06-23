#include "../Common/Init.h"
#include "Main.h"

int main(int argc, char** argv)
{
    xwin::init(argc, argv);

            display = wl_display_connect(nullptr);

        if (display == nullptr) {
            printf(
                "Cannot find a compatible Vulkan installable client driver "
                "(ICD).\nExiting ...\n");
            fflush(stdout);
            exit(1);
        }

        registry = wl_display_get_registry(display);
        wl_registry_add_listener(registry, &registry_listener, this);
        wl_display_dispatch(display);

    xmain(argc, argv);

    wl_shell_surface_destroy(shell_surface);
    wl_surface_destroy(window);
    wl_shell_destroy(shell);
    wl_compositor_destroy(compositor);
    wl_registry_destroy(registry);
    wl_display_disconnect(display);
    
    return 0;
}