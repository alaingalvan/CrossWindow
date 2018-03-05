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
		/*
		window = [[NSWindow alloc]
							initWithContentRect: rect
							styleMask: styleMask
							backing: NSBackingStoreBuffered
							defer: NO];
		*/
		//[window setTitle: @"New Window"];
		//[window center];
		
		NSPoint point = NSMakePoint(desc.x, desc.y);
		//[window setFrameOrigin: point];
		//[window makeKeyAndOrderFront:nil];

	return true;
	}
	
	void MacWindow::destroy()
	{
		//[pool release];
	}
	
	bool MacWindow::eventLoop() {
		//check Common Window events with Mac Events
		return false;
	}
	

	

}
