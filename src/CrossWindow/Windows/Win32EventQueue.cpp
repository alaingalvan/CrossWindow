#include "Win32EventQueue.h"

namespace xwin
{
Win32EventQueue::Win32EventQueue()
{
}

bool Win32EventQueue::update()
{
    MSG msg = {};
    while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
    {
        //Translate virtual key messages
        TranslateMessage(&msg);

        //push to abstract event queue
        pushEvent(msg);

        //dispatch events to their coresponding windows
        DispatchMessage(&msg);
    }

    return true;
}

void Win32EventQueue::pushEvent(MSG msg)
{
    UINT message = msg.message;

    switch (message)
    {
    case WM_CREATE:
        mQueue.emplace(xwin::EventType::Create);
    break;
    case WM_PAINT:
        mQueue.emplace(xwin::EventType::Paint);
    break;
    case WM_DESTROY:
        mQueue.emplace(xwin::EventType::Close);
        break;
    case WM_SETFOCUS:
        mQueue.emplace(xwin::EventType::Focus);
        break;
    case WM_KILLFOCUS:
        mQueue.emplace(xwin::EventType::Unfocus);
        break;
    case WM_MOUSEWHEEL:
        (short) HIWORD(msg.wParam);
        break;
    case WM_LBUTTONDOWN:
        mQueue.emplace(xwin::EventType::Mouse);
        break;
    case WM_LBUTTONUP:
        mQueue.emplace(xwin::EventType::Mouse);
        break;
    case WM_MOUSEMOVE:
        mQueue.emplace(xwin::EventType::Mouse);
        break;
    case WM_KEYDOWN:

        DigitalInput d;

        switch (msg.wParam)
        {
        case VK_ESCAPE:
            d = DigitalInput::Escape;
            break;
        case 0x30:
            d = DigitalInput::Num0;
            break;
        case 0x31:
            d = DigitalInput::Num1;
            break;
        case 0x32:
            d = DigitalInput::Num2;
            break;
        case 0x33:
            d = DigitalInput::Num3;
            break;
        case 0x34:
            d = DigitalInput::Num4;
            break;
        case 0x35:
            d = DigitalInput::Num5;
            break;
        case 0x36:
            d = DigitalInput::Num6;
            break;
        case 0x37:
            d = DigitalInput::Num7;
            break;
        case 0x38:
            d = DigitalInput::Num8;
            break;
        case 0x39:
            d = DigitalInput::Num9;
            break;
        case 0x41:
            d = DigitalInput::A;
            break;
        case 0x42:
            d = DigitalInput::B;
            break;
        case 0x43:
            d = DigitalInput::C;
            break;
        case 0x44:
            d = DigitalInput::D;
            break;
        case 0x45:
            d = DigitalInput::E;
            break;
        case 0x46:
            d = DigitalInput::F;
            break;
        case 0x47:
            d = DigitalInput::G;
            break;
        case 0x48:
            d = DigitalInput::H;
            break;
        case 0x49:
            d = DigitalInput::I;
            break;
        case 0x4A:
            d = DigitalInput::J;
            break;
        case 0x4B:
            d = DigitalInput::K;
            break;
        case 0x4C:
            d = DigitalInput::L;
            break;
        case 0x4D:
            d = DigitalInput::M;
            break;
        case 0x4E:
            d = DigitalInput::N;
            break;
        case 0x4F:
            d = DigitalInput::O;
            break;
        case 0x50:
            d = DigitalInput::P;
            break;
        case 0x51:
            d = DigitalInput::Q;
            break;
        case 0x52:
            d = DigitalInput::R;
            break;
        case 0x53:
            d = DigitalInput::S;
            break;
        case 0x54:
            d = DigitalInput::T;
            break;
        case 0x55:
            d = DigitalInput::U;
            break;
        case 0x56:
            d = DigitalInput::V;
            break;
        case 0x57:
            d = DigitalInput::W;
            break;
        case 0x58:
            d = DigitalInput::X;
            break;
        case 0x59:
            d = DigitalInput::Y;
            break;
        case 0x5A:
            d = DigitalInput::Z;
            break;
        case VK_NUMPAD0:
            d = DigitalInput::Numpad0;
            break;
        case VK_NUMPAD1:
            d = DigitalInput::Numpad1;
            break;
        case VK_NUMPAD2:
            d = DigitalInput::Numpad2;
            break;
        case VK_NUMPAD3:
            d = DigitalInput::Numpad3;
            break;
        case VK_NUMPAD4:
            d = DigitalInput::Numpad4;
            break;
        case VK_NUMPAD5:
            d = DigitalInput::Numpad5;
            break;
        case VK_NUMPAD6:
            d = DigitalInput::Numpad6;
            break;
        case VK_NUMPAD7:
            d = DigitalInput::Numpad7;
            break;
        case VK_NUMPAD8:
            d = DigitalInput::Numpad8;
            break;
        case VK_NUMPAD9:
            d = DigitalInput::Numpad9;
            break;
        case VK_UP:
            d = DigitalInput::Up;
            break;
        case VK_LEFT:
            d = DigitalInput::Left;
            break;
        case VK_DOWN:
            d = DigitalInput::Down;
            break;
        case VK_RIGHT:
            d = DigitalInput::Right;
            break;
        case VK_SPACE:
            d = DigitalInput::Space;
            break;
        case VK_HOME:
            d = DigitalInput::Home;
            break;

        default:
            d = DigitalInput::DigitalInputKeysMax;
            break;
        }

        mQueue.emplace(EventType::DigitalInput, new DigitalInputData(d));
        break;
    case WM_SIZE:
        unsigned width, height;
        width = (unsigned)(UINT)(UINT64)msg.lParam & 0xFFFF;
        height = (unsigned)(UINT)(UINT64)msg.lParam >> 16;

        mQueue.emplace(EventType::Resize, new ResizeData(width, height));
        break;
    default:
        // Do nothing
        break;
    }
}

const Event &Win32EventQueue::front()
{
    return mQueue.front();
}

void Win32EventQueue::pop()
{
    mQueue.pop();
}

bool Win32EventQueue::empty()
{
    return mQueue.empty();
}
} // namespace xwin