#include "Event.h"

#include <unordered_map>

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
    : type(EventType::MouseMove), window(window)
{
    data.mouseMove = d;
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

Event::Event(DpiData d, Window* window) : type(EventType::DPI), window(window)
{
    data.dpi = d;
}

Event::~Event() {}

ResizeData::ResizeData(unsigned width, unsigned height, bool resizing)
    : width(width), height(height), resizing(resizing)
{
}

/**
 * A map of the Keys enum to chars for matching keyboard event data.
 * Convenient for converting xwin::Key(s) to strings for serialization
 * Though for certain platforms that natively support this
 * (Mac OS, iOS, WebAssembly) we should opt to use those functions.
 */
static KeyToCharMap sKeyToCharMap = {
    "\x1B", "1", "2",  "3",  "4", "5", "6", "7", "8", "9", "0", "-", "=", "\b",
    "\t", "Q", "W",  "E",  "R", "T", "Y", "U", "I", "O", "P", "[", "]", "\r",
    "",   "A", "S",  "D",  "F", "G", "H", "J", "K", "L", ";", ":", "'", "\"",
    "`",  "",  "\\", "Z",  "X", "C", "V", "B", "N", "M", ",", ".", "/", "",
    "*",  "",  " ",  "",   "",  "",  "",  "",  "",  "",  "",  "",  "",  "",
    "",   "",  "7",  "8",  "9", "-", "4", "5", "6", "+", "1", "2", "3", "0",
    ".",  "",  "",   "\r", "",  "/", "",  "",  "",  "",  "",  "",  "",  "",
    "",   "",  "",   "",   "",  "",  "",  ""};

static std::unordered_map<const char*, Key> sCharToKeyMap = {
    {"\x1B", Key::Escape},
    {"1", Key::Num1},
    {"2", Key::Num2},
    {"3", Key::Num3},
    {"4", Key::Num4},
    {"5", Key::Num5},
    {"6", Key::Num6},
    {"7", Key::Num7},
    {"8", Key::Num8},
    {"9", Key::Num9},
    {"0", Key::Num0},
    {"-", Key::Subtract},
    {"=", Key::Equals},
    {"\b", Key::Back},
    {"\t", Key::Tab},
    {"Q", Key::Q},
    {"W", Key::W},
    {"E", Key::E},
    {"R", Key::R},
    {"T", Key::T},
    {"Y", Key::Y},
    {"U", Key::U},
    {"I", Key::I},
    {"O", Key::O},
    {"P", Key::P},
    {"[", Key::LBracket},
    {"]", Key::RBracket},
    {"\r", Key::Enter},
    {"A", Key::A},
    {"S", Key::S},
    {"D", Key::D},
    {"F", Key::F},
    {"G", Key::G},
    {"H", Key::H},
    {"J", Key::J},
    {"K", Key::K},
    {"L", Key::L},
    {";", Key::Semicolon},
    {":", Key::Colon},
    {"'", Key::Apostrophe},
    {"\"", Key::Semicolon},
    {"`", Key::Grave},
    {"Left Shift", Key::LShift},
    {"\\", Key::Backslash},
    {"Z", Key::Z},
    {"X", Key::X},
    {"C", Key::C},
    {"V", Key::V},
    {"B", Key::B},
    {"N", Key::N},
    {"M", Key::M},
    {".", Key::Period},
    {"/", Key::Slash},
    {"Right Shift", Key::RShift},
    {"*", Key::Multiply},
    {"Left Alt", Key::LAlt},
    {" ", Key::Space},
    {"Captial", Key::Capital},
    {"F1", Key::F1},
    {"F2", Key::F2},
    {"F3", Key::F3},
    {"F4", Key::F4},
    {"F5", Key::F5},
    {"F6", Key::F6},
    {"F7", Key::F7},
    {"F8", Key::F8},
    {"F9", Key::F9},
    {"F10", Key::F10},
    {"Numlock", Key::Numlock},
};

const char* convertKeyToString(Key key)
{
    return sKeyToCharMap[static_cast<size_t>(key)];
}

Key convertStringToKey(const char* str)
{
    Key k = Key::KeysMax;
    auto itr = sCharToKeyMap.find(str);
    if (itr != sCharToKeyMap.end())
    {
        k = (*itr).second;
    }
    return k;
}

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
DpiData::DpiData(float scale) : scale(scale) {}
}
