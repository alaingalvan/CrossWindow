#include "CocoaEventQueue.h"
#import <Cocoa/Cocoa.h>

namespace xwin
{
void EventQueue::update()
{
    // Update Application
    NSApplication* nsApp = (NSApplication*)getXWinState().application;
    @autoreleasepool
    {
        NSEvent* nsEvent = nil;
        
        do
        {
            nsEvent = [nsApp nextEventMatchingMask:NSEventMaskAny untilDate:nil inMode:NSDefaultRunLoopMode dequeue:YES];
            Event curEvent;
            switch(nsEvent.type)
            {
                case NSEventTypeSystemDefined:
                    
                    break;
                case NSEventTypeKeyDown:
                {
                    // Check single characters
                    Key d = Key::KeysMax;
                    NSString* characters = [nsEvent characters];
                    if ([characters length] > 0)
                    {
                        switch([characters characterAtIndex:0])
                        {
                            case 'a':
                            case 'A':
                                d = Key::A;
                                break;
                            case 'b':
                            case 'B':
                                d = Key::B;
                                break;
                            default:
                                break;
                        }
                    }
                    characters = [nsEvent charactersIgnoringModifiers];
                    if ([characters length] > 0)
                    {
                        //KeyboardCodeFromCharCode([characters characterAtIndex:0]);
                    }
                    
                    // Finally check Key Codes for escape, arrows, etc.
                    switch([nsEvent keyCode])
                    {
                        case 0x7B:
                            d = Key::Left;
                            break;
                        case 0x7C:
                            d = Key::Right;
                            break;
                        default:
                            break;
                    }
                    
                    if (d != Key::KeysMax)
                    {
                    }
                }
                    break;
                case NSEventTypeKeyUp:
                    ;
                    break;
                case NSEventTypeLeftMouseDown:
                    curEvent = Event(
                                     MouseInputData(
                                                    MouseInput::Left, ButtonState::Pressed,
                                                    xwin::ModifierState(nsEvent.modifierFlags & NSEventModifierFlagControl, nsEvent.modifierFlags & NSEventModifierFlagOption,
                                                                        nsEvent.modifierFlags & NSEventModifierFlagShift, nsEvent.modifierFlags & NSEventModifierFlagCommand)));
                    break;
                case NSEventTypeLeftMouseUp:
                    curEvent = xwin::Event(
                                           xwin::MouseInputData(
                                                                MouseInput::Left, ButtonState::Released,
                                                                xwin::ModifierState(nsEvent.modifierFlags & NSEventModifierFlagControl, nsEvent.modifierFlags & NSEventModifierFlagOption,
                                                                                    nsEvent.modifierFlags & NSEventModifierFlagShift, nsEvent.modifierFlags & NSEventModifierFlagCommand)));
                    break;
                case NSEventTypeRightMouseDown:
                    curEvent = xwin::Event(
                                           xwin::MouseInputData(
                                                                MouseInput::Right, ButtonState::Pressed,
                                                                xwin::ModifierState(nsEvent.modifierFlags & NSEventModifierFlagControl, nsEvent.modifierFlags & NSEventModifierFlagOption,
                                                                                    nsEvent.modifierFlags & NSEventModifierFlagShift, nsEvent.modifierFlags & NSEventModifierFlagCommand)));
                    break;
                case NSEventTypeRightMouseUp:
                    curEvent = xwin::Event(
                                           xwin::MouseInputData(
                                                                MouseInput::Right, ButtonState::Released,
                                                                xwin::ModifierState(nsEvent.modifierFlags & NSEventModifierFlagControl, nsEvent.modifierFlags & NSEventModifierFlagOption,
                                                                                    nsEvent.modifierFlags & NSEventModifierFlagShift, nsEvent.modifierFlags & NSEventModifierFlagCommand)));
                    break;
                case NSEventTypeMouseMoved:
                    curEvent = xwin::Event(
                                           xwin::MouseMoveData(
                                                               static_cast<unsigned>(nsEvent.absoluteX), static_cast<unsigned>(nsEvent.absoluteY),
                                                               static_cast<unsigned>(nsEvent.absoluteX), static_cast<unsigned>(nsEvent.absoluteY),
                                                               static_cast<int>(nsEvent.deltaX),
                                                               static_cast<int>(nsEvent.deltaY))
                                           );
                    break;
                case NSEventTypeScrollWheel:
                    [nsEvent deltaY];
                    
                    break;
                default:
                    break;
            }
            if(curEvent.type != EventType::None)
            {
                mQueue.push(curEvent);
            }
            
            [NSApp sendEvent:nsEvent];
        }
        while (nsEvent);
        
    }
    [nsApp updateWindows];
}

const Event& EventQueue::front()
{
    return mQueue.front();
}

void EventQueue::pop()
{
    mQueue.pop();
}

bool EventQueue::empty()
{
    return mQueue.empty();
}


}
