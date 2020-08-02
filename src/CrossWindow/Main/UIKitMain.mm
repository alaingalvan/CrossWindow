#include "../Common/Init.h"
#include "Main.h"

#import <UIKit/UIKit.h>
#import <TargetConditionals.h>
#import <Availability.h>

@interface XWinAppDelegate : NSObject<UIApplicationDelegate>
{
}

- (void)run;

@end

@implementation XWinAppDelegate

- (void)applicationWillResignActive:(UIApplication *)application {
    // Sent when the application is about to move from active to inactive state. This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and it begins the transition to the background state.
    // Use this method to pause ongoing tasks, disable timers, and throttle down OpenGL ES frame rates. Games should use this method to pause the game.
}

- (void)applicationDidEnterBackground:(UIApplication *)application {
    // Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later.
    // If your application supports background execution, this method is called instead of applicationWillTerminate: when the user quits.
}

- (void)applicationWillEnterForeground:(UIApplication *)application {
    // Called as part of the transition from the background to the inactive state; here you can undo many of the changes made on entering the background.
}

- (void)applicationDidBecomeActive:(UIApplication *)application {
    // Restart any tasks that were paused (or not yet started) while the application was inactive. If the application was previously in the background, optionally refresh the user interface.
}

- (void)applicationWillTerminate:(UIApplication *)application {
    // Called when the application is about to terminate. Save data if appropriate. See also applicationDidEnterBackground:.
}

- (void)deviceOrientationDidChange: (NSNotification* )notification
{
	
}

- (void)run
{
	const xwin::XWinState& state = xwin::getXWinState();
	xmain(state.argc, (const char**)state.argv);
}

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
    // Register orientation changes notifications
    [[UIDevice currentDevice] beginGeneratingDeviceOrientationNotifications];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(deviceOrientationDidChange:) name:UIDeviceOrientationDidChangeNotification object: nil];

    // Change the working directory to the resources directory
    [[NSFileManager defaultManager] changeCurrentDirectoryPath: [[NSBundle mainBundle] resourcePath]];
	
	// iOS doesn't feature command line arguments
	xwin::init(0, nullptr, application);
	
	//schedule call to run CrossWindow Main
    [self performSelector:@selector(run) withObject:nil afterDelay:0.0];

    return true;
}


@end

int main(int argc, const char * argv[])
{
	// iOS does not feature command line app execution
	// And manages application lifecycles directly:
	return UIApplicationMain(argc, (char**)argv, nil, @"XWinAppDelegate");

}
