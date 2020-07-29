#include "../Common/Init.h"
#include "Main.h"

#import <UIKit/UIKit.h>
#import <TargetConditionals.h>
#import <Availability.h>

@interface XWinApplication : UIApplication
{

}

- (void)run;

@end

@implementation XWinApplication

- (void)run
{
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
