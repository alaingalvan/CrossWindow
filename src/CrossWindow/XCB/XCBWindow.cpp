#include "XCBWindow.h"

namespace xwin
{
Window::Window() {}

// Request that this window be minimized.
void Window::minimize() {}

// Request that this window be maximized.
void Window::maximize() {}

// Set callback func
void Window::trackEventsAsync(
    const std::function<void(const xwin::Event e)>& fun)
{
    mCallback = fun;
}

// Executes an event callback asynchronously, use this for non-blocking
// events (resizing while rendering, etc.)
void Window::executeEventCallback(const xwin::Event e)
{
    switch (e.type)
    {
    case EventType::Create:
        break;
    case EventType::Close:
        break;
    case EventType::Focus:
        break;
    case EventType::Paint:
        break;
    case EventType::Resize:
        break;
    case EventType::DPI:
        break;
    case EventType::Keyboard:
        break;
    case EventType::MouseMove:
        break;
    case EventType::MouseRaw:
        break;
    case EventType::MouseWheel:
        break;
    case EventType::MouseInput:
        break;
    case EventType::Touch:
        break;
    case EventType::Gamepad:
        break;
    case EventType::DropFile:
        break;
    case EventType::HoverFile:
        break;
    default:
        // EventType::None
        // EventType::EventTypeMax
        break;
    }
}

bool Window::create(const WindowDesc& desc, EventQueue& eventQueue)
{
    const XWinState& xwinState = getXWinState();
    connection = xwinState.connection;
    screen = xwinState.screen;

    window = xcb_generate_id(connection);

    uint32_t mask = XCB_CW_BACK_PIXEL | XCB_CW_EVENT_MASK;
    uint32_t value_list[2] = {
        screen->black_pixel,
        XCB_EVENT_MASK_EXPOSURE | XCB_EVENT_MASK_BUTTON_PRESS |
            XCB_EVENT_MASK_BUTTON_RELEASE | XCB_EVENT_MASK_POINTER_MOTION |
            XCB_EVENT_MASK_ENTER_WINDOW | XCB_EVENT_MASK_LEAVE_WINDOW |
            XCB_EVENT_MASK_KEY_PRESS | XCB_EVENT_MASK_KEY_RELEASE};

    xcb_create_window(connection, XCB_COPY_FROM_PARENT, window, screen->root,
                      desc.x, desc.y, desc.width, desc.height, 0,
                      XCB_WINDOW_CLASS_INPUT_OUTPUT, screen->root_visual, mask,
                      value_list);

    xcb_map_window(connection, window);

    const unsigned coords[] = {static_cast<unsigned>(desc.x),
                               static_cast<unsigned>(desc.y)};
    xcb_configure_window(connection, window,
                         XCB_CONFIG_WINDOW_X | XCB_CONFIG_WINDOW_Y, coords);

    xcb_flush(connection);

    return true;
}

void Window::close() { xcb_destroy_window(connection, window); }

}
