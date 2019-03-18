#pragma once

#include <stddef.h>

/**
 * Events in CrossWindow are heavily influenced by:
 * - winit by Pierre Krieger <https://github.com/tomaka/winit>
 * - W3's DOM Events
 * <https://dvcs.w3.org/hg/dom3events/raw-file/tip/html/DOM3-Events.html>
 */
namespace xwin
{
class Window;

enum class EventType : size_t
{
    None = 0,

    // Closing a window
    Close,

    // Creating a window
    Create,

    // Focus/Unfocus on a window
    Focus,

    // Paint events, a good time to present any graphical changes
    Paint,

    // Resizing a window
    Resize,

    // Change in the screen DPI scaling (such as moving a window to a monitor
    // with a larger DPI.
    DPI,

    // Keyboard input such as press/release events
    Keyboard,

    // Mouse moving events
    MouseMoved,

    // Raw mouse data events
    MouseRaw,

    // Mouse scrolling events
    MouseWheel,

    // Mouse button press events
    MouseInput,

    // Touch events
    Touch,

    // Gamepad Input Events such as analog sticks, button presses
    Gamepad,

    // Dropping a file on the window
    DropFile,

    // Hovering a file over a window
    HoverFile,

    EventTypeMax
};

/**
 * Focus data passed with Focus events
 */
struct FocusData
{
    // true if focused, false if not
    bool focused;

    FocusData(bool focused);

    static const EventType type = EventType::Focus;
};

/**
 * Resize data passed with Resize events
 */
struct ResizeData
{
    // new width of window viewport
    unsigned width;

    // New height of window viewport
    unsigned height;

    ResizeData(unsigned width, unsigned height);

    static const EventType type = EventType::Resize;
};

/**
 * DPI data passed with DPI events
 */
struct DPIData
{
    float scale;

    static const EventType type = EventType::DPI;
};

/**
 * The state of a button press, be it keyboard, mouse, etc.
 */
enum ButtonState : size_t
{
    Pressed = 0,
    Released,
    ButtonStateMax
};

/**
 * The state of modifier keys such as ctrl, alt, shift, and the windows/command
 * buttons. Pressed is true, released is false;
 */
struct ModifierState
{
    // Ctrl key
    bool ctrl;

    // Alt key
    bool alt;

    // Shift key
    bool shift;

    // Meta buttons such as the Windows button or Mac's Command button
    bool meta;

    ModifierState(bool ctrl = false, bool alt = false, bool shift = false,
                  bool meta = false);
};

/**
 * Key event enum
 */
enum class Key : size_t
{
    // Keyboard
    Escape = 0,
    Num1,
    Num2,
    Num3,
    Num4,
    Num5,
    Num6,
    Num7,
    Num8,
    Num9,
    Num0,
    Minus,
    Equals,
    Back,
    Tab,
    Q,
    W,
    E,
    R,
    T,
    Y,
    U,
    I,
    O,
    P,
    LBracket,
    RBracket,
    Enter,
    LControl,
    A,
    S,
    D,
    F,
    G,
    H,
    J,
    K,
    L,
    Semicolon,
    Apostrophe,
    Grave,
    LShift,
    Backslash,
    Z,
    X,
    C,
    V,
    B,
    N,
    M,
    Comma,
    Period,
    Slash,
    RShift,
    Multiply,
    LAlt,
    Space,
    Capital,
    F1,
    F2,
    F3,
    F4,
    F5,
    F6,
    F7,
    F8,
    F9,
    F10,
    Numlock,
    Scroll,
    Numpad7,
    Numpad8,
    Numpad9,
    Subtract,
    Numpad4,
    Numpad5,
    Numpad6,
    Add,
    Numpad1,
    Numpad2,
    Numpad3,
    Numpad0,
    Decimal,
    F11,
    F12,
    Numpadenter,
    RControl,
    Divide,
    sysrq,
    RAlt,
    Pause,
    Home,
    Up,
    PgUp,
    Left,
    Right,
    End,
    Down,
    PgDn,
    Insert,
    Del,
    LWin,
    RWin,
    Apps,

    KeysMax
};

typedef const char* KeyToCharMap[static_cast<size_t>(Key::KeysMax)];
typedef Key CharToKeyMap[static_cast<size_t>(Key::KeysMax)];

/**
 * A map of the Keys enum to chars for matching keyboard event data.
 * Convenient for converting xwin::Key(s) to strings for serialization
 */
static KeyToCharMap sKeyToCharMap;

/**
 * Converts a key to a string for serialization
 */
const char* convertKeyToString(Key key);

/**
 * A map of strings to Keys for matching keyboard event data.
 * Useful for deserialization of strings to xwin::Keys
 */
static CharToKeyMap sCharToKeyMap;

/**
 * Converts a string name to a xwin::Key for deserialization
 */
Key convertStringToKey(const char* str);

/**
 * Data sent during keyboard events
 */
struct KeyboardData
{
    Key key;
    ButtonState state;
    ModifierState modifiers;

    static const EventType type = EventType::Keyboard;

    KeyboardData(Key key, ButtonState state, ModifierState modifiers);
};

struct MouseRawData
{
    int deltax;
    int deltay;

    static const EventType type = EventType::MouseRaw;

    MouseRawData(int deltax, int deltay);
};

/**
 * The event data passed with mouse events click, mouse moving events
 */
struct MouseMoveData
{
    // Current x position relative to active window
    unsigned x;

    // Current y position relative to active window
    unsigned y;

    // Current global x position
    unsigned screenx;

    // Current in global y position
    unsigned screeny;

    // Change in x relative to previous event, used for FPS motion
    int deltax;

    // Change in y relative to previous event, used for FPS motion
    int deltay;

    static const EventType type = EventType::MouseMoved;

    MouseMoveData(unsigned x, unsigned y, unsigned screenx, unsigned screeny,
                  int deltax, int deltay);
};

enum MouseInput
{
    Left,
    Right,
    Middle,
    Button4,
    Button5,
    MouseInputMax
};

/**
 * Data passed with mouse input events
 */
struct MouseInputData
{
    MouseInput button;
    ButtonState state;
    ModifierState modifiers;
    static const EventType type = EventType::MouseInput;

    MouseInputData(MouseInput button, ButtonState state,
                   ModifierState modifiers);
};

/**
 * Data passed with mouse wheel events
 */
struct MouseWheelData
{
    double delta;
    ModifierState modifiers;
    static const EventType type = EventType::MouseWheel;

    MouseWheelData(double delta, ModifierState modifiers);
};

/**
 * Touch point data
 */
struct TouchPoint
{
    // A unique id for each touch point
    unsigned long id;

    // touch coordinate relative to whole screen origin in pixels
    unsigned screenX;

    // touch coordinate relative to whole screen origin in pixels
    unsigned screenY;

    // touch coordinate relative to window in pixels.
    unsigned clientX;

    // touch coordinate relative to window in pixels.
    unsigned clientY;

    // Did the touch point change
    bool isChanged;
};

/**
 * Data passed for touch events
 */
struct TouchData
{
    unsigned numTouches;

    TouchPoint touches[32];

    static const EventType type = EventType::Touch;
};

/**
 * Gamepad Button pressed enum
 */
enum class GamepadButton : size_t
{
    DPadUp = 0,
    DPadDown,
    DPadLeft,
    DPadRight,
    StartButton,
    BackButton,
    LThumbClick,
    RThumbClick,
    LShoulder,
    RShoulder,
    AButton,
    BButton,
    XButton,
    YButton,
    GamepadButtonMax
};

/**
 * Gamepad analog stick enum
 */
enum class AnalogInput : size_t
{
    // gamepad
    AnalogLeftTrigger,
    AnalogRightTrigger,
    AnalogLeftStickX,
    AnalogLeftStickY,
    AnalogRightStickX,
    AnalogRightStickY,

    // mouse
    AnalogMouseX,
    AnalogMouseY,
    AnalogMouseScroll,

    AnalogInputsMax
};

typedef const char*
    AnalogToStringMap[static_cast<size_t>(AnalogInput::AnalogInputsMax)];

/**
 * Data passed for gamepad events
 */
struct GamepadData
{
    // If the gamepad is connected or not
    bool connected;

    // Gamepad Index
    size_t index;

    // String id of the brand of the gamepad
    const char* id;

    // String id that lays out controller mapping (Southpaw, etc.)
    const char* mapping;

    // Analog Axis input data, such as joysticks, normalized range [-1, 1]
    double axis[64];

    // The number of analog axes
    unsigned numAxes;

    // Analog gamepad buttons like triggers, bound to [0, 1].
    double analogButton[64];

    bool digitalButton[64];

    // Number of digital buttons and analog buttons
    unsigned numButtons;

    static const EventType type = EventType::Gamepad;
};

/**
 * SDL does something similar:
 * <https://www.libsdl.org/release/SDL-1.2.15/docs/html/sdlevent.html>
 */
union EventData {
    FocusData focus;
    ResizeData resize;
    DPIData dpi;
    KeyboardData keyboard;
    MouseMoveData mouseMoved;
    MouseInputData mouseInput;
    MouseWheelData mouseWheel;
    TouchData touch;
    GamepadData gamepad;
    MouseRawData mouseRaw;

    EventData() {}

    ~EventData() {}
};

class Event
{
  public:
    Event(EventType type, Window* window);

    Event(FocusData data, Window* window);

    Event(ResizeData data, Window* window);

    Event(KeyboardData data, Window* window);

    Event(MouseMoveData data, Window* window);

	Event(MouseRawData data, Window* window);

    Event(MouseInputData data, Window* window);

    Event(MouseWheelData data, Window* window);

    Event(TouchData data, Window* window);

    Event(GamepadData data, Window* window);

    ~Event();

    // The event's type
    const EventType type;

    // Pointer to a CrossWindow window
    Window* window;

    // Inner data of the event
    EventData data;
};
}