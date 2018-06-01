#include "MacOSEventQueue.h"
#import <Cocoa/Cocoa.h>

namespace xwin
{
	bool MacOSEventQueue:: update()
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
						DigitalInput d = DigitalInput::DigitalInputMax;
						NSString* characters = [e characters];
						if ([characters length] > 0)
						{
							switch([characters characterAtIndex:0])
							{
								case 'a':
								case 'A':
									d = DigitalInput::A;
									break;
								case 'b':
								case 'B':
									d = DigitalInput::B;
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
								d = DigitalInput::Left;
								break;
							case 0x7C:
								d = DigitalInput::Right;
								break;
							default:
								break;
						}

						if (d != DigitalInput::DigitalInputMax)
						{
							 mQueue.emplace(xwin::EventType::DigitalInput, d);
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
						mQueue.emplace(xwin::EventType::Mouse);
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
	
	
}
