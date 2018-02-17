#include "Init.h"
#include "State.h"

namespace xwin
{
namespace
{
XWinState xWinState;
}
}

bool xwin::init(MainArgs)
{
  xWinState = XWinState(MainArgsVars);
  return true;
}
xwin::XWinState &xwin::getXWinState()
{
  return xWinState;
}