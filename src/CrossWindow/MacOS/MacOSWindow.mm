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
	std::vector<xwin::Event> mEventQueue;


}
- (BOOL)	acceptsFirstResponder;
- (BOOL)	isOpaque;

- (void)	keyUp:(NSEvent*)event;
- (void)	keyDown:(NSEvent*)event;
@end

@implementation XWinView

-(void)keyUp:(NSEvent*)event
{
    NSLog(@"Key %@", event);
}

-(void)keyDown:(NSEvent*)event
{   
    switch( [event keyCode] )
		{
        case 126:
        case 125:
        case 124: 
        case 123:       
  // Arrow Keys
   break;
        default:
   // Key not supported
   break;
    }
}

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
		destroy();
	}
	
	bool MacWindow::create(const WindowDesc &desc)
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
	
	void MacWindow::destroy()
	{
		[(XWinWindow*)mWindow release];
		[(XWinView*)mView release];
	}
	
	bool MacWindow::eventLoop()
	{
		// Update Application
		NSApplication* nsApp = (NSApplication*)getXWinState().application;
		@autoreleasepool
		{
			NSEvent* e = nil;
			
			do
			{
				e = [nsApp nextEventMatchingMask:NSEventMaskAny untilDate:nil inMode:NSDefaultRunLoopMode dequeue:YES];
				[NSApp sendEvent:e];
			}
			while (e);
			
		}
		[nsApp updateWindows];

		//return mView.eventQueue;

		return false;
	}
	

	

}
