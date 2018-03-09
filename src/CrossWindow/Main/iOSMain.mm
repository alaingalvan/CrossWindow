#include "../Common/Init.h"
#include "Main.h"

#import <AppKit/AppKit.h>

int main(int argc, const char * argv[])
{
	xwin::init(argc, argv);
	return NSApplicationMain(argc, argv);
}