#include "../Common/Init.h"
#include "./Main.h"

#import <Cocoa/Cocoa.h>

@interface XWinApplication : NSApplication
{

}

- (void)run;

@end

@implementation XWinApplication

- (void)run
{
	[[NSNotificationCenter defaultCenter]
		postNotificationName:NSApplicationWillFinishLaunchingNotification
		object:NSApp];
	[[NSNotificationCenter defaultCenter]
		postNotificationName:NSApplicationDidFinishLaunchingNotification
		object:NSApp];
	
	const xwin::XWinState& state = xwin::getXWinState();
	xmain(state.argc, (const char**)state.argv);
}

@end


int main(int argc, char** argv)
{
	NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
	
	NSApplication* applicationObject = [XWinApplication alloc];
	
	xwin::init(argc, (const char**)argv, applicationObject);

	if ([applicationObject respondsToSelector:@selector(run)])
	{
		[applicationObject
			performSelectorOnMainThread:@selector(run)
			withObject:nil
			waitUntilDone:YES];
	}
	
	[pool release];
	
	return 0;
}
