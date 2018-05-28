#include "../Common/Init.h"
#include "Main.h"

#import <AppKit/AppKit.h>

@interface XWinApplication : UIApplication
{

}

- (void)run;

@end

@implementation UIApplication

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

int main(int argc, const char * argv[])
{
	NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
	
	UIApplication* applicationObject = [XWinApplication alloc];
	
	xwin::init(argc, (const char**)argv, applicationObject);

	if ([applicationObject respondsToSelector:@selector(run)])
	{
		[applicationObject
			performSelectorOnMainThread:@selector(run)
			withObject:nil
			waitUntilDone:YES];
	}
	
	[pool release];
}