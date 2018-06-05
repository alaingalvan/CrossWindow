#pragma once

#include <stddef.h>

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

        // Paint events, a good time to present any graphical changes
        Paint,

        // Resizing a window
        Resize,

        // Keyboard input such as press/release events
        Keyboard,

        // Mouse events such as clicking, moving, etc.
        Mouse,

        MouseMoved,

        // Mouse scrolling events
        MouseWheel,

        // Mouse button press events
        MouseInput,

        // Digital input such as keyboard press/release, gamepad, etc.
        DigitalInput, //Gamepad

        // Analog input such as gamepad joysticks
        AnalogInput,

        // Touch events
        Touch,

        // Focus on a window
        Focus,

        // Unfocus on a window
        Unfocus,

        EventTypeMax
    };

    /**
     * The state of a button press, be it keyboard, mouse, etc.
     */ 
    enum ButtonState : size_t
    {
        Pressed,
        Released
    };

    enum class DigitalInput : size_t
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

        DigitalInputKeysMax,

        // Gamepad
        DPadUp = DigitalInputKeysMax,
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

        // Mouse
        Mouse0,
        Mouse1,
        Mouse2,
        Mouse3,
        Mouse4,
        Mouse5,
        Mouse6,
        Mouse7,

        DigitalInputMax
    };

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

    struct TouchPoint
    {
        // An id for each touch point
        unsigned long id;

        // touch coordinate relative to whole screen origin in pixels
        unsigned screenX;
        unsigned screenY;

        // touch coordinate relative to window in pixels.
        unsigned clientX;
        unsigned clientY;

        // Did the touch point change 
        bool isChanged;
    };

    struct TouchData
    {
        unsigned numTouches;

        TouchPoint touches[32];
    };

    struct GamepadData
    {
        // Event timestamp
        double timestamp;
        
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


    };

    struct KeyboardData
    {
        DigitalInput key;
        ButtonState state;
        //ModifierState modifiers;
    };

    /**
     * Resize data passed with Resize events
     */
    class ResizeData
    {
    public:
        static const EventType type = EventType::Resize;

        unsigned width;
        unsigned height;
        ResizeData(unsigned width, unsigned height);
    };

    /**
     * Event data passed with digital input events such as keypress, keydown, and keyup, gamepad
     */
    class DigitalInputData
    {
    public:
        static const EventType type = EventType::DigitalInput;

        DigitalInput key;
        bool pressed;
        bool released;
        unsigned modifiers;

        DigitalInputData(DigitalInput key);
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
     * The event data passed with mouse events click, mousedown, mouseup, mousemove, mousenter, mouseleave, mousewheel
     */
    struct MouseData
    {
        static const EventType type = EventType::Mouse;
        unsigned x;
        unsigned y;
    };


    union EventData
    {
        ResizeData resize;
        DigitalInputData digitalInput;
        MouseData mouse;
        EventData()
        {}
        ~EventData()
        {}
    };

    class Event
    {
    public:

        Event(EventType type);

        Event(ResizeData data);

        Event(MouseData data);

        Event(DigitalInputData data);

        ~Event();

        // The event's type
        const EventType type;

        /**
         * The data attribute coresponds with the current event's type.
         * Ideally the type is infered from the return value context.
         */
        template<typename T>
        constexpr T getData() const;

        // Pointer to a CrossWindow window
        Window* window;

    protected:
        EventData _data;
    };

    template<typename T>
    inline constexpr T Event::getData() const
    {
        if (type != T::type)
        {
            //stop compilation
        }
        return _data.mouse;
    }
}