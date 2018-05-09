#include "../Common/Init.h"
#include "Main.h"

#import <Cocoa/Cocoa.h>

int MyApplicationMain(int argc, const char **argv);

@interface MyApplication : NSApplication
{
	bool shouldKeepRunning;
}

- (void)run;
- (void)terminate:(id)sender;

@end


int MyApplicationMain(int argc, const char **argv)
{
	NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
	
	NSDictionary *infoDictionary = [[NSBundle mainBundle] infoDictionary];
	Class principalClass = NSClassFromString([infoDictionary objectForKey:@"NSPrincipalClass"]);
	NSApplication *applicationObject = [principalClass sharedApplication];

	NSString *mainNibName = [infoDictionary objectForKey:@"NSMainNibFile"];
	NSNib *mainNib = [[NSNib alloc] initWithNibNamed:mainNibName bundle:[NSBundle mainBundle]];
	[mainNib instantiateNibWithOwner:applicationObject topLevelObjects:nil];

	if ([applicationObject respondsToSelector:@selector(run)])
	{
		[applicationObject
			performSelectorOnMainThread:@selector(run)
			withObject:nil
			waitUntilDone:YES];
	}
	
	[mainNib release];
	[pool release];
	
	return 0;
}

@implementation MyApplication

- (void)run
{
//	[self finishLaunching];
	[[NSNotificationCenter defaultCenter]
		postNotificationName:NSApplicationWillFinishLaunchingNotification
		object:NSApp];
	[[NSNotificationCenter defaultCenter]
		postNotificationName:NSApplicationDidFinishLaunchingNotification
		object:NSApp];
	
	// TODO: this should be called in MacOSWindow.mm
	/*
	shouldKeepRunning = YES;
	do
	{
		NSEvent *event =
			[self
				nextEventMatchingMask:NSAnyEventMask
				untilDate:[NSDate distantFuture]
				inMode:NSDefaultRunLoopMode
				dequeue:YES];
		
		[self sendEvent:event];
		[self updateWindows];
	} while (shouldKeepRunning);
	*/
	XWinState& state = getXWinState();
	xmain(state.argc, state.argv);
}

- (void)terminate:(id)sender
{
	shouldKeepRunning = NO;
}

@end


int main(int argc, char** argv)
{
	xwin::init(argc, argv);
	return MyApplicationMain(argc, argv);
}