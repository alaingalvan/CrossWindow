#include "CocoaEventQueue.h"
#import <Cocoa/Cocoa.h>

namespace xwin
{
	void MacOSEventQueue::update()
	{
		// Update Application
		NSApplication* nsApp = (NSApplication*)getXWinState().application;
		@autoreleasepool
		{
			NSEvent* e = nil;
			
			do
			{
				e = [nsApp nextEventMatchingMask:NSEventMaskAny untilDate:nil inMode:NSDefaultRunLoopMode dequeue:YES];
				
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
						
						break;
					case NSEventTypeLeftMouseUp:
						
						break;
					case NSEventTypeRightMouseDown:
						
						break;
					case NSEventTypeRightMouseUp:
						
						break;
					case NSEventTypeOtherMouseUp:
						
						break;
					case NSEventTypeMouseMoved:
						
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
	
	const Event& MacOSEventQueue::front()
	{
		return mQueue.front();
	}
	
	void MacOSEventQueue::pop()
	{
		mQueue.pop();
	}
	
	bool MacOSEventQueue::empty()
	{
		return mQueue.empty();
	}
	
	
}
