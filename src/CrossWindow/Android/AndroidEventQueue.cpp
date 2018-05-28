#include "AndroidEventQueue.h"

namespace xwin
{
bool AndroidEventQueue::update()
{
  int events;
  struct android_poll_source *source;
  while (ALooper_pollAll(active ? 0 : -1, NULL, &events, (void **)&source) >= 0) {
      if (source) {
          source->process(app, source);
      }

      if (app->destroyRequested != 0) {
          demo_cleanup(&demo);
          return;
      }
  }
}

static int32_t processInput(struct android_app *app, AInputEvent *event) { return 0; }

static void processCommand(struct android_app *app, int32_t cmd) {
    switch (cmd) {
        case APP_CMD_INIT_WINDOW: {
            if (app->window) {
                // We're getting a new window.  If the app is starting up, we
                // need to initialize.  If the app has already been
                // initialized, that means that we lost our previous window,
                // which means that we have a lot of work to do.  At a minimum,
                // we need to destroy the swapchain and surface associated with
                // the old window, and create a new surface and swapchain.
                // However, since there are a lot of other objects/state that
                // is tied to the swapchain, it's easiest to simply cleanup and
                // start over (i.e. use a brute-force approach of re-starting
                // the app)
                if (demo.prepared) {
                    demo_cleanup(&demo);
                }

                // Parse Intents into argc, argv
                // Use the following key to send arguments, i.e.
                // --es args "--validate"
                const char key[] = "args";
                char *appTag = (char *)APP_SHORT_NAME;
                int argc = 0;
                char **argv = get_args(app, key, appTag, &argc);

                __android_log_print(ANDROID_LOG_INFO, appTag, "argc = %i", argc);
                for (int i = 0; i < argc; i++) __android_log_print(ANDROID_LOG_INFO, appTag, "argv[%i] = %s", i, argv[i]);

                demo_init(&demo, argc, argv);

                // Free the argv malloc'd by get_args
                for (int i = 0; i < argc; i++) free(argv[i]);

                demo.window = (void *)app->window;
                demo_init_vk_swapchain(&demo);
                demo_prepare(&demo);
                initialized = true;
            }
            break;
        }
        case APP_CMD_GAINED_FOCUS: {
            active = true;
            break;
        }
        case APP_CMD_LOST_FOCUS: {
            active = false;
            break;
        }
    }
}
}