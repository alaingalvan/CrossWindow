#include "Main.h"
#include "../Common/Init.h"

#import <Cocoa/Cocoa.h>


int main(int argc, const char * argv[]) {
	xwin::init(argc, argv);
	return NSApplicationMain(argc, argv);
}