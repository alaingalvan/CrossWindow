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
	XWinView* v = (XWinView*)view;
	CGRect rect = v.frame;
	if( !desc.fullscreen)
	{
		rect.size.width = desc.width;
		rect.size.height = desc.height;
	}
	view = [v initWithFrame:rect];
	
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
		XWinView* v = (XWinView*)view;
		CAMetalLayer* l = (CAMetalLayer*)v.layer;
		l.pixelFormat = MTLPixelFormatRGBA16Float;
		l.drawableSize = v.frame.size;
	}
	else if(type == LayerType::OpenGL)
	{
		//OpenGL is currently depreciated, and unavailable in UIKit
	}
}

}
