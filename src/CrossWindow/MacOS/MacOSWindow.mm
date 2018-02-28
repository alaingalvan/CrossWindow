#include "MacOSWindow.h"

namespace xwin
{
	MacWindow::MacWindow()
	{
	}
	
	MacWindow::~MacWindow()
	{
	}
	
	
	bool MacWindow::create(const WindowDesc &desc) {
		NSRect rect = NSMakeRect(desc.x, desc.y, desc.width, desc.height);
		NSWindowStyleMask styleMask = NSWindowStyleMaskTitled | NSWindowStyleMaskClosable | NSWindowStyleMaskResizable | NSWindowStyleMaskMiniaturizable;
		
		pool = [[NSAutoreleasePool alloc] init];
		app = [[NSApplication alloc] init];
		window = [[NSWindow alloc]
							initWithContentRect: rect
							styleMask: styleMask
							backing: NSBackingStoreBuffered
							defer: NO];
		
		[window setTitle: @"New Window"];
		[window center];
		[window makeKeyAndOrderFront:nil];
		[app run];
		[pool release];
	return true;
	}
	
	void MacWindow::destroy()
	{
		[pool release];
	}
	
	bool MacWindow::eventLoop() {
		//check Common Window events with Mac Events
		return false;
	}
	

	

}

@interface CrossApplication : NSApplication
{
	NSArray* nibObjects;
}

@end

@implementation CrossApplication

// From http://cocoadev.com/index.pl?GameKeyboardHandlingAlmost
// This works around an AppKit bug, where key up events while holding
// down the command key don't get sent to the key window.
- (void)sendEvent:(NSEvent *)event
{
	if ([event type] == NSEventTypeKeyUp &&
		([event modifierFlags] & NSEventModifierFlagCommand))
	{
		[[self keyWindow] sendEvent:event];
	}
	else
		[super sendEvent:event];
}


// No-op thread entry point
//
- (void)doNothing:(id)object
{
}

- (void)loadMainMenu
{
#if MAC_OS_X_VERSION_MAX_ALLOWED >= 100800
	[[NSBundle mainBundle] loadNibNamed:@"MainMenu"
								  owner:NSApp
						topLevelObjects:&nibObjects];
#else
	[[NSBundle mainBundle] loadNibNamed:@"MainMenu" owner:NSApp];
#endif
}
@end
