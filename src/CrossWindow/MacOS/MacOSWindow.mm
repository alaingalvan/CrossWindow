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
	
	bool MacWindow::create(const WindowDesc &desc)
	{
		NSApplication* nsApp = (NSApplication*)getXWinState().nsApp;

		NSRect rect = NSMakeRect(desc.x, desc.y, desc.width, desc.height);
		NSWindowStyleMask styleMask = NSWindowStyleMaskTitled | NSWindowStyleMaskClosable | NSWindowStyleMaskResizable | NSWindowStyleMaskMiniaturizable;
		
		// Setup NSWindow
		mWindow = [[NSWindow alloc]
							initWithContentRect: rect
							styleMask: styleMask
							backing: NSBackingStoreBuffered
							defer: NO];

		mTitle = [NSString stringWithCString:desc.title.c_str() 
                                   encoding:[NSString defaultCStringEncoding]];
		[(NSWindow*)mWindow setTitle: (NSString*)mTitle];
		[(NSWindow*)mWindow center];
		
		NSPoint point = NSMakePoint(desc.x, desc.y);
		[(NSWindow*)mWindow setFrameOrigin: point];
		
		// Setup NSView
		mView = [[NSView alloc] initWithFrame:rect];
		[mView setHidden:NO];
		[mView setNeedsDisplay:YES];
		[(NSWindow*)mWindow setContentView:tmpView];
		[(NSWindow*)mWindow makeKeyAndOrderFront:nsApp];

	return true;
	}
	
	void MacWindow::destroy()
	{
		[(NSWindow*)mWindow release];
		[(NSView*)mView release]
	}
	
	bool MacWindow::eventLoop()
	{
		NSApplication* nsApp = (NSApplication*)getXWinState().nsApp;

		while( NSEvent* e = [nsApp nextEventMatchingMask:NSEventMaskAny untilDate:[NSDate distantFuture] inMode:NSEventTrackingRunLoopMode dequeue:YES] )
		{
			[nsApp sendEvent:event];

			//TODO: fill event loop with event abstractions
		}

		// This may be redundant with multiple windows, but is probably fine ~ ag
		[nsApp updateWindows];

		return false;
	}
	

	

}
