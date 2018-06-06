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
            mQueue.emplace(xwin::FocusData(true));
            break;
        case WM_KILLFOCUS:
            mQueue.emplace(xwin::FocusData(false));
            break;
        case WM_MOUSEWHEEL:
        {
            (short)HIWORD(msg.wParam);
            break;
        }
        case WM_LBUTTONDOWN:

            break;
        case WM_LBUTTONUP:

            break;
        case WM_MOUSEMOVE:

            break;
        case WM_KEYDOWN:

            Key d;

            switch (msg.wParam)
            {
            case VK_ESCAPE:
                d = Key::Escape;
                break;
            case 0x30:
                d = Key::Num0;
                break;
            case 0x31:
                d = Key::Num1;
                break;
            case 0x32:
                d = Key::Num2;
                break;
            case 0x33:
                d = Key::Num3;
                break;
            case 0x34:
                d = Key::Num4;
                break;
            case 0x35:
                d = Key::Num5;
                break;
            case 0x36:
                d = Key::Num6;
                break;
            case 0x37:
                d = Key::Num7;
                break;
            case 0x38:
                d = Key::Num8;
                break;
            case 0x39:
                d = Key::Num9;
                break;
            case 0x41:
                d = Key::A;
                break;
            case 0x42:
                d = Key::B;
                break;
            case 0x43:
                d = Key::C;
                break;
            case 0x44:
                d = Key::D;
                break;
            case 0x45:
                d = Key::E;
                break;
            case 0x46:
                d = Key::F;
                break;
            case 0x47:
                d = Key::G;
                break;
            case 0x48:
                d = Key::H;
                break;
            case 0x49:
                d = Key::I;
                break;
            case 0x4A:
                d = Key::J;
                break;
            case 0x4B:
                d = Key::K;
                break;
            case 0x4C:
                d = Key::L;
                break;
            case 0x4D:
                d = Key::M;
                break;
            case 0x4E:
                d = Key::N;
                break;
            case 0x4F:
                d = Key::O;
                break;
            case 0x50:
                d = Key::P;
                break;
            case 0x51:
                d = Key::Q;
                break;
            case 0x52:
                d = Key::R;
                break;
            case 0x53:
                d = Key::S;
                break;
            case 0x54:
                d = Key::T;
                break;
            case 0x55:
                d = Key::U;
                break;
            case 0x56:
                d = Key::V;
                break;
            case 0x57:
                d = Key::W;
                break;
            case 0x58:
                d = Key::X;
                break;
            case 0x59:
                d = Key::Y;
                break;
            case 0x5A:
                d = Key::Z;
                break;
            case VK_NUMPAD0:
                d = Key::Numpad0;
                break;
            case VK_NUMPAD1:
                d = Key::Numpad1;
                break;
            case VK_NUMPAD2:
                d = Key::Numpad2;
                break;
            case VK_NUMPAD3:
                d = Key::Numpad3;
                break;
            case VK_NUMPAD4:
                d = Key::Numpad4;
                break;
            case VK_NUMPAD5:
                d = Key::Numpad5;
                break;
            case VK_NUMPAD6:
                d = Key::Numpad6;
                break;
            case VK_NUMPAD7:
                d = Key::Numpad7;
                break;
            case VK_NUMPAD8:
                d = Key::Numpad8;
                break;
            case VK_NUMPAD9:
                d = Key::Numpad9;
                break;
            case VK_UP:
                d = Key::Up;
                break;
            case VK_LEFT:
                d = Key::Left;
                break;
            case VK_DOWN:
                d = Key::Down;
                break;
            case VK_RIGHT:
                d = Key::Right;
                break;
            case VK_SPACE:
                d = Key::Space;
                break;
            case VK_HOME:
                d = Key::Home;
                break;

            default:
                d = Key::KeysMax;
                break;
            }
            break;
        case WM_SIZE:
            unsigned width, height;
            width = (unsigned)(UINT)(UINT64)msg.lParam & 0xFFFF;
            height = (unsigned)(UINT)(UINT64)msg.lParam >> 16;

            mQueue.emplace(ResizeData(width, height));
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
}