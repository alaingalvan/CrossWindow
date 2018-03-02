#ifdef XWIN_MACOS || XWIN_IOS
#import <Cocoa/Cocoa.h>

int main(int argc, const char * argv[]) {
	return NSApplicationMain(argc, argv);
}
#endif