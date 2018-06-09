#include "iOSWindow.h"

#import <UIKit/UIKit.h>

@interface XWinViewController : UIViewController
@end

@implementation XWinViewController
{
  CADDisplayLink* _displayLink;
}

@end

@interface XWinView : UIView
@end

@implementation XWinView

@end

namespace xwin
{
  bool IOSWindow::update()
  {
    return false;
  }
}