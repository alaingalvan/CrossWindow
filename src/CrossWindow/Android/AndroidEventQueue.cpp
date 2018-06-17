#include "AndroidEventQueue.h"

namespace xwin
{
    AndroidEventQueue::AndroidEventQueue()
    {
        struct android_app* app = xwin::getXWinState().state;
        app->onAppCmd = processCommand;
        app->onInputEvent = processInput;
    }

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

    static int32_t processInput(struct android_app *app, AInputEvent* event)
    {
        int32_t type = AInputEvent_getType(event);
        if (type == AINPUT_EVENT_TYPE_KEY)
        {
            DigitalInput d;
            int32_t keyCode = AKeyEvent_getKeyCode(event);
            switch (keyCode)
            {
            case AKEYCODE_Z:
                d = DigitalInput::Z;
                break;
            default:
                break;
            }
        }
        else if (type = AINPUT_EVENT_TYPE_MOTION)
        {

        }
        return 0;
    }

    static void processCommand(struct android_app *app, int32_t cmd) {
        switch (cmd) {
        case APP_CMD_INIT_WINDOW:
        {
            (void *)app->window;


        }
        break;
        case APP_CMD_GAINED_FOCUS:
        {


        }
        break;
        case APP_CMD_LOST_FOCUS:
        {

        }
        break;
        }
    }
}