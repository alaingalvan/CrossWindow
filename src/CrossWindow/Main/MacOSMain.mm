#include "../Common/Init.h"
#include "Main.h"

#import <Cocoa/Cocoa.h>

int main(int argc, char** argv)
{
	xwin::init(argc, argv);
	return NSApplicationMain(argc, argv);
}