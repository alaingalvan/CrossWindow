#include "UIKitWindow.h"

#import <UIKit/UIKit.h>
#import <QuartzCore/CAMetalLayer.h>

@interface XWinViewController : UIViewController
@end

@implementation XWinViewController
{
}

@end

@interface XWinView : UIView

@end

@implementation XWinView
+ (Class) layerClass
{
    return [CAMetalLayer class];
}
@end

namespace xwin
{


Window::Window()
{
	window =
	view =
	layer = nullptr;
}

Window::~Window()
{
	if( window != nullptr)
	{
		close();
	}
}

bool Window::create(const WindowDesc& desc, EventQueue& eventQueue)
{
	UIApplication* nsApp = (UIApplication*)getXWinState().application;
	
    // Configure view
	view = [XWinView alloc];
	CGRect rect = ((XWinView*)view).frame;
	if( !desc.fullscreen)
	{
		rect.size.width = desc.width;
		rect.size.height = desc.height;
	}
	view = [view initWithFrame:rect];
    view.colorPixelFormat = MTLPixelFormatRGBA16Float;
    view.sampleCount = 1;
	view.drawableSize = _view.frame.size;
	eventQueue.update();
	
	mDesc = desc;
	
	return true;
}

WindowDesc Window::getDesc()
{
	return mDesc;
}

bool Window::update()
{
	return false;
}

void Window::close()
{
	//[(XWinWindow*)window release];
	[(XWinView*)view release];
	
	window = nullptr;
	view = nullptr;
	layer = nullptr;
}

void Window::setLayer(LayerType type)
{
	if(type == LayerType::Metal)
	{
		//According to Apple Docs, you must assign this layer via
		//an override to `+ (Class) layerClass`
	}
	else if(type == LayerType::OpenGL)
	{
		//OpenGL is currently depreciated, and unavailable in UIKit s
	}
}

}
