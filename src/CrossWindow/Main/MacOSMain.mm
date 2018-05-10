#include "../Common/Init.h"
#include "Main.h"

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
	
	const XWinState& state = getXWinState();
	xmain(state.argc, state.argv);
}

@end


int main(int argc, char** argv)
{
	NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
	
	NSDictionary* infoDictionary = [[NSBundle mainBundle] infoDictionary];
	Class principalClass = NSClassFromString([infoDictionary objectForKey:@"NSPrincipalClass"]);
	NSApplication* applicationObject = [principalClass sharedApplication];
	
	xwin::init(argc, argv, applicationObject);

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