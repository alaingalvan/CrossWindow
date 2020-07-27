#include "UIKitWindow.h"

#import <UIKit/UIKit.h>

@interface XWinViewController : UIViewController
@end

@implementation XWinViewController
{
  CADisplayLink* _displayLink;
}

@end

@interface XWinView : UIView
@end

@implementation XWinView

@end

namespace xwin
{
  bool Window::update()
  {
    return false;
  }
}
