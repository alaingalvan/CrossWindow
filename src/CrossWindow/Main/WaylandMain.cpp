#include "../Common/Init.h"
#include "Main.h"

#include <wayland-client-core.h>
#include <wayland-client-protocol.h>
#include <wayland-client.h>

int main(int argc, const char** argv)
{
    struct wl_display* display = wl_display_connect(nullptr);
    if (!display) return 1;

    struct wl_registry* registry = wl_display_get_registry(display);
    const struct wl_registry_listener registry_listener
    {
        nullptr, nullptr // callbacks
    };
    struct wl_compositor* compositor;
    wl_registry_add_listener(registry, &registry_listener, &compositor);
    wl_display_roundtrip(display);
    wl_registry_destroy(registry);

    xwin::init(argc, argv, display);

    xmain(argc, argv);

    wl_compositor_destroy(compositor);
    wl_display_disconnect(display);

    return 0;
}
