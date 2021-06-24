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
			NSEvent* e = nil;
			
			do
			{
				e = [nsApp nextEventMatchingMask:NSEventMaskAny untilDate:nil inMode:NSDefaultRunLoopMode dequeue:YES];
				xwin::Event curEvent = xwin::Event(xwin::EventType::None, window);
				switch(e.type)
				{
					case NSEventTypeSystemDefined:
						
						break;
					case NSEventTypeKeyDown:
					{
            // Check single characters
						Key d = Key::KeysMax;
						NSString* characters = [e characters];
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
            characters = [e charactersIgnoringModifiers];
            if ([characters length] > 0)
            {
              //KeyboardCodeFromCharCode([characters characterAtIndex:0]);
            }
						
						// Finally check Key Codes for escape, arrows, etc.
						switch([e keyCode])
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
							mQueue.emplace(KeyboardData(d, ButtonState::Pressed, ModifierState()), nullptr);
						}
					}
						break;
					case NSEventTypeKeyUp:
						
						break;
					case NSEventTypeLeftMouseDown:
						        e = xwin::Event(
            xwin::MouseInputData(
                MouseInput::Left, ButtonState::Pressed,
                xwin::ModifierState(modifiers & MK_CONTROL, modifiers & MK_ALT,
                                    modifiers & MK_SHIFT, modifiers & 0)),
            window);
						break;
					case NSEventTypeLeftMouseUp:
						        e = xwin::Event(
            xwin::MouseInputData(
                MouseInput::Left, ButtonState::Pressed,
                xwin::ModifierState(modifiers & MK_CONTROL, modifiers & MK_ALT,
                                    modifiers & MK_SHIFT, modifiers & 0)),
            window);
						break;
					case NSEventTypeRightMouseDown:
						        e = xwin::Event(
            xwin::MouseInputData(
                MouseInput::Left, ButtonState::Pressed,
                xwin::ModifierState(modifiers & MK_CONTROL, modifiers & MK_ALT,
                                    modifiers & MK_SHIFT, modifiers & 0)),
            window);
						break;
					case NSEventTypeRightMouseUp:
						        e = xwin::Event(
            xwin::MouseInputData(
                MouseInput::Left, ButtonState::Pressed,
                xwin::ModifierState(modifiers & MK_CONTROL, modifiers & MK_ALT,
                                    modifiers & MK_SHIFT, modifiers & 0)),
            window);
						break;
					case NSEventTypeOtherMouseUp:
						        e = xwin::Event(
            xwin::MouseInputData(
                MouseInput::Left, ButtonState::Pressed,
                xwin::ModifierState(modifiers & MK_CONTROL, modifiers & MK_ALT,
                                    modifiers & MK_SHIFT, modifiers & 0)),
            window);
						break;
					case NSEventTypeMouseMoved:
						        curEvent = xwin::Event(
            xwin::MouseMoveData(
                static_cast<unsigned>(area.left <= x && x <= area.right
                                          ? x - area.left
                                          : 0xFFFFFFFF),
                static_cast<unsigned>(area.top <= y && y <= area.bottom
                                          ? y - area.top
                                          : 0xFFFFFFFF),
                static_cast<unsigned>(x), static_cast<unsigned>(y),
                static_cast<int>(x - prevMouseX),
                static_cast<int>(y - prevMouseY)),
            window);
        prevMouseX = static_cast<unsigned>(x);
        prevMouseY = static_cast<unsigned>(y);
						break;
					case NSEventTypeScrollWheel:
						[e deltaY];
						
						break;
					default:
						break;
				}
				
				
				[NSApp sendEvent:e];
			}
			while (e);
			
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
