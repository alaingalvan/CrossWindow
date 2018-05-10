#include "MacOSWindow.h"
#import <Cocoa/Cocoa.h>

namespace xwin
{

	NSString* stringToNSString(const std::string& string)
	{
		NSString* str = [NSString stringWithCString:string.c_str() encoding:NSUTF8StringEncoding];
		return str;
	}

	
	MacWindow::MacWindow()
	{
	}
	
	MacWindow::~MacWindow()
	{
		destroy();
	}
	
	bool MacWindow::create(const WindowDesc &desc) {

		NSRect rect = NSMakeRect(desc.x, desc.y, desc.width, desc.height);
		NSWindowStyleMask styleMask = NSWindowStyleMaskTitled | NSWindowStyleMaskClosable | NSWindowStyleMaskResizable | NSWindowStyleMaskMiniaturizable;
		mWindow = [[NSWindow alloc]
							initWithContentRect: rect
							styleMask: styleMask
							backing: NSBackingStoreBuffered
							defer: NO];

		mTitle = [NSString stringWithCString:desc.title.c_str() 
                                   encoding:[NSString defaultCStringEncoding]];
		[mWindow setTitle: mTitle];
		[mWindow center];
		
		NSPoint point = NSMakePoint(desc.x, desc.y);
		[window setFrameOrigin: point];
		[window makeKeyAndOrderFront:nil];

	return true;
	}
	
	void MacWindow::destroy()
	{
		[mWindow release];
	}
	
	bool MacWindow::eventLoop()
	{
		NSApplication* nsApp = getXWinState().nsApp;

		while( NSEvent* e = [nsApp nextEventMatchingMask:NSEventMaskAny untilDate:[NSDate distantFuture] inMode:NSEventTrackingRunLoopMode dequeue:YES] )
		{
			[nsApp sendEvent:event];

			//TODO: fill event loop with event abstractions
		}

		// This may be redundant ~ ag
		[nsApp updateWindows];

		return false;
	}
	

	

}
