#include "Event.h"

namespace xwin
{
Event::Event(EventType type, Window* window) : type(type), window(window) {}

Event::Event(FocusData d, Window* window)
    : type(EventType::Focus), window(window)
{
    data.focus = d;
}

Event::Event(ResizeData d, Window* window)
    : type(EventType::Resize), window(window)
{
    data.resize = d;
}

Event::Event(KeyboardData d, Window* window)
    : type(EventType::Keyboard), window(window)
{
    data.keyboard = d;
}

Event::Event(MouseRawData d, Window* window)
    : type(EventType::MouseRaw), window(window)
{
    data.mouseRaw = d;
}


Event::Event(MouseMoveData d, Window* window)
    : type(EventType::MouseMoved), window(window)
{
    data.mouseMoved = d;
}

Event::Event(MouseInputData d, Window* window)
    : type(EventType::MouseInput), window(window)
{
    data.mouseInput = d;
}

Event::Event(MouseWheelData d, Window* window)
    : type(EventType::MouseWheel), window(window)
{
    data.mouseWheel = d;
}

Event::Event(TouchData d, Window* window)
    : type(EventType::Touch), window(window)
{
    data.touch = d;
}

Event::Event(GamepadData d, Window* window)
    : type(EventType::Gamepad), window(window)
{
    data.gamepad = d;
}

Event::~Event() {}

ResizeData::ResizeData(unsigned width, unsigned height)
    : width(width), height(height)
{
}

const char* convertKeyToString(Key key) { return nullptr; }

Key convertStringToKey(const char* str) { return Key(); }

FocusData::FocusData(bool focused) : focused(focused) {}

ModifierState::ModifierState(bool ctrl, bool alt, bool shift, bool meta)
    : ctrl(ctrl), alt(alt), shift(shift), meta(meta)
{
}

MouseMoveData::MouseMoveData(unsigned x, unsigned y, unsigned screenx,
                             unsigned screeny, int deltax, int deltay)
    : x(x), y(y), screenx(screenx), screeny(screeny), deltax(deltax),
      deltay(deltay)
{
}

MouseInputData::MouseInputData(MouseInput button, ButtonState state,
                               ModifierState modifiers)
    : button(button), state(state), modifiers(modifiers)
{
}

KeyboardData::KeyboardData(Key key, ButtonState state, ModifierState modifiers)
    : key(key), state(state), modifiers(modifiers)
{
}

MouseWheelData::MouseWheelData(double delta, ModifierState modifiers)
    : delta(delta), modifiers(modifiers)
{
}

MouseRawData::MouseRawData(int deltax, int deltay)
    : deltax(deltax), deltay(deltay)
{
}
}