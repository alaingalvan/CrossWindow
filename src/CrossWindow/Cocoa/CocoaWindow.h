#pragma once

#include "../Common/EventQueue.h"
#include "../Common/Init.h"
#include "../Common/WindowDesc.h"

#include <vector>

namespace xwin
{
/**
 * Wrapper Window for a NSWindow and it's various children.
 */ 
class Window
{
  public:
    Window();

    ~Window();

    // Initialize this window with the Cocoa API.
    bool create(const WindowDesc& desc, EventQueue& eventQueue);

    // Get this Window's descriptor object.
    xwin::WindowDesc getDesc();

    // Request that this window be closed.
    void close();

    // Set the mouse position in display space.
    void setMousePosition(unsigned x, unsigned y);

    // Get the size of the current display this window is in.
    UVec2 getCurrentDisplaySize();

    // MacOS Only Functions:

    enum class LayerType
    {
        Metal,
        OpenGL,
        LayerTypeMax
    };

    // Set the type of this window's view layer
    void setLayer(LayerType type);

  protected:
    // NSString*
    void* mTitle;

    WindowDesc mDesc;

    // XWinWindow*
    void* window;

    // XWinView*
    void* view;

    // Any Layer Type
    void* layer;

    /**
     * MacOS Keycodes:
     * https://stackoverflow.com/questions/3202629/where-can-i-find-a-list-of-mac-virtual-key-codes
     */
    typedef Key MacKeycodeToDigitalInputMap[1 << (8 * sizeof(unsigned char))];
};

}
