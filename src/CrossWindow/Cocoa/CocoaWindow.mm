#include "MacOSWindow.h"
#import <Cocoa/Cocoa.h>

@interface XWinWindow : NSWindow
{
}
@end

@implementation XWinWindow

@end

@interface XWinView : NSView
{
@public
- (BOOL)	acceptsFirstResponder;
- (BOOL)	isOpaque;
@end

@implementation XWinView

- (BOOL)acceptsFirstResponder
{
	return YES;
}

- (BOOL)isOpaque
{
	return YES;
}

@end


namespace xwin
{	
	MacWindow::MacWindow()
	{
	}
	
	MacWindow::~MacWindow()
	{
		if( mWindow != nullptr)
		{
			close();
		}
	}
	
	bool MacWindow::create(const WindowDesc& desc, EventQueue& eventQueue)
	{
		NSApplication* nsApp = (NSApplication*)getXWinState().application;

		NSRect rect = NSMakeRect(desc.x, desc.y, desc.width, desc.height);
		NSWindowStyleMask styleMask = NSWindowStyleMaskTitled | NSWindowStyleMaskClosable | NSWindowStyleMaskResizable | NSWindowStyleMaskMiniaturizable;
		
		// Setup NSWindow
		mWindow = [[XWinWindow alloc]
							initWithContentRect: rect
							styleMask: styleMask
							backing: NSBackingStoreBuffered
							defer: NO];

		mTitle = [NSString stringWithCString:desc.title.c_str() 
                                   encoding:[NSString defaultCStringEncoding]];
		[(XWinWindow*)mWindow setTitle: (NSString*)mTitle];
		[(XWinWindow*)mWindow center];
		
		NSPoint point = NSMakePoint(desc.x, desc.y);
		[(XWinWindow*)mWindow setFrameOrigin: point];
		
		// Setup NSView
		mView = [[XWinView alloc] initWithFrame:rect];
		[(XWinView*)mView setHidden:NO];
		[(XWinView*)mView setNeedsDisplay:YES];
		[(XWinWindow*)mWindow setContentView:(XWinView*)mView];
		[(XWinWindow*)mWindow makeKeyAndOrderFront:nsApp];

	return true;
	}
	
	void MacWindow::close()
	{
		[(XWinWindow*)mWindow release];
		[(XWinView*)mView release];
		mWindow = nullptr;
		mView = nullptr;
	}
}
