#include "Window.h"
#import <Cocoa/Cocoa.h>
#import <QuartzCore/CAMetalLayer.h>

@interface XWinWindow : NSWindow
{
}
@end

@implementation XWinWindow

@end

@interface XWinView : NSView
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
	Window::Window()
	{
	}
	
	Window::~Window()
	{
		if( window != nullptr)
		{
			close();
		}
	}
	
	bool Window::create(const WindowDesc& desc, EventQueue& eventQueue, Window* parent)
	{
		NSApplication* nsApp = (NSApplication*)getXWinState().application;

		NSRect rect = NSMakeRect(desc.x, desc.y, desc.width, desc.height);
		NSWindowStyleMask styleMask = NSWindowStyleMaskTitled | NSWindowStyleMaskClosable | NSWindowStyleMaskResizable | NSWindowStyleMaskMiniaturizable;
		
		// Setup NSWindow
		window = [[XWinWindow alloc]
							initWithContentRect: rect
							styleMask: styleMask
							backing: NSBackingStoreBuffered
							defer: NO];

		mTitle = [NSString stringWithCString:desc.title.c_str() 
                                   encoding:[NSString defaultCStringEncoding]];
		[(XWinWindow*)window setTitle: (NSString*)mTitle];
		[(XWinWindow*)window center];
		
		NSPoint point = NSMakePoint(desc.x, desc.y);
		[(XWinWindow*)window setFrameOrigin: point];
		
		// Setup NSView
		view = [[XWinView alloc] initWithFrame:rect];
		[(XWinView*)view setHidden:NO];
		[(XWinView*)view setNeedsDisplay:YES];
		[(XWinWindow*)window setContentView:(XWinView*)view];
		[(XWinWindow*)window makeKeyAndOrderFront:nsApp];
		[(XWinView*)view setWantsLayer:YES];
		
		eventQueue.update();
		
	return true;
	}
	
	void Window::close()
	{
		[(XWinWindow*)window release];
		[(XWinView*)view release];
		[(CALayer*)layer release];
		
		window = nullptr;
		view = nullptr;
		layer = nullptr;
	}
	
	void Window::setLayer(LayerType type)
	{
		[(XWinView*)view setWantsLayer:YES];
		
		layer = [[CAMetalLayer alloc] init];
							   [(XWinView*)view setLayer:(CAMetalLayer*)layer];
	}
	
	
	void Window::setMousePosition(unsigned x, unsigned y)
	{
		CGPoint pos = CGPointMake(x, y);
		CGWarpMouseCursorPosition(pos);
	}
	
	UVec2 Window::getCurrentDisplaySize()
	{
		UVec2 size;
		NSRect screenRect = [[NSScreen mainScreen] frame];
		size.x = screenRect.size.width;
		size.y = screenRect.size.height;
		return size;
	}
}
