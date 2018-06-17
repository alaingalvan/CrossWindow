#pragma once

#include <emscripten/html5.h>
#include <emscripten/key_codes.h>
#include <emscripten.h>

namespace xwin
{
  /**
   * The bulk of this class was built from the documentation and test suite of Emscripten:
   * 
   * Docs - http://kripken.github.io/emscripten-site/docs/api_reference/html5.h.html
   * Tests - https://github.com/kripken/emscripten/tree/master/tests
   */ 
  class WASMEventQueue
  {
    public:
    WASMEventQueue();

    /**
     * Update the event queue with new events received from the Emscripten instance
     * Returns if the queue has been updated.
     */
    void update();

    protected:

    // Key pressed / released events
    static EM_BOOL keyCallback(int eventType, const EmscriptenKeyboardEvent *e, void *userData);

    // Mouse movement / buttons
    static EM_BOOL mouseCallback(int eventType, const EmscriptenMouseEvent *mouseEvent, void *userData);

    // Mouse Scrolling
    static EM_BOOL mouseWheelCallback(int eventType, const EmscriptenWheelEvent *wheelEvent, void *userData);

    // Fullscreen events
    static EM_BOOL fullscreenCallback(int eventType, const EmscriptenFullscreenChangeEvent *fullscreenChangeEvent, void *userData);

    // Focus of DOM elements events
    static EM_BOOL focusCallback(int eventType, const EmscriptenFocusEvent *focusEvent, void *userData);

    static const char * pageUnloadCallback(int eventType, const void *reserved, void *userData)

    // Games

    // Gamepad events
    static EM_BOOL gamepadCallback(int eventType, const EmscriptenGamepadEvent *gamepadEvent, void *userData);
    
    //Mobile / Tablet

    // Touch events
    static EM_BOOL touchCallback(int eventType, const EmscriptenTouchEvent *touchEvent, void *userData);

    // Portrait / Landscape events
    static EM_BOOL orientationCallback(int eventType, const EmscriptenOrientationChangeEvent *orientationChangeEvent, void *userData)

    // Orientation of the device in terms of the transformation from a coordinate frame fixed on the Earth to a coordinate frame fixed in the device.
    static EM_BOOL deviceOrientationCallback(int eventType, const EmscriptenDeviceOrientationEvent *deviceOrientationEvent, void *userData);

    //CrossWindow users aren't allowed to vibrate the device, because that's annoying ~ ag
    //bool vibrate(int screwthat);
    
    // Movement of the device (acceleration/rotation delta)
    static EM_BOOL motionCallback(int eventType, const EmscriptenDeviceMotionEvent *deviceMotionEvent, void *userData);
    
    // Device battery
    static EM_BOOL batteryCallback(int eventType, const EmscriptenBatteryEvent *batteryEvent, void *userData);

  };

    typedef WASMEventQueue EventQueueDelegate;
}