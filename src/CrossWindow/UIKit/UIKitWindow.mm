#include "UIKitWindow.h"

#import <UIKit/UIKit.h>

@interface XWinViewController : UIViewController
@end

@implementation XWinViewController
{
	CADisplayLink* _displayLink;
}

@end

@interface XWinView : UIView
@end

@implementation XWinView

@end

namespace xwin
{


Window::Window()
{
	window =
	view =
	layer = nullptr;
}

Window::~Window()
{
	if( window != nullptr)
	{
		close();
	}
}

bool Window::create(const WindowDesc& desc, EventQueue& eventQueue)
{
	UIApplication* nsApp = (UIApplication*)getXWinState().application;
	/*
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
	*/
	// Setup NSView
	//view = [[XWinView alloc] initWithFrame:rect];
	[(XWinView*)view setHidden:NO];
	//[(XWinView*)view setNeedsDisplay:YES];
	//[(XWinWindow*)window setContentView:(XWinView*)view];
	//[(XWinWindow*)window makeKeyAndOrderFront:nsApp];
	//[(XWinView*)view setWantsLayer:YES];
	
	eventQueue.update();
	
	mDesc = desc;
	
	return true;
}

WindowDesc Window::getDesc()
{
	return mDesc;
}

bool Window::update()
{
	return false;
}

void Window::close()
{
	//[(XWinWindow*)window release];
	[(XWinView*)view release];
	[(CALayer*)layer release];
	
	window = nullptr;
	view = nullptr;
	layer = nullptr;
}

void Window::setLayer(LayerType type)
{
	if(type == LayerType::Metal)
	{
		XWinView* v = (XWinView*)view;
		layer = [[CAMetalLayer alloc] init];
		[v displayLayer:(CAMetalLayer*)layer];
	}
	else if(type == LayerType::OpenGL)
	{
		//OpenGL is currently unsupported
	}
}

}
