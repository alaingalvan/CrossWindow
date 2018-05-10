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
const xwin::XWinState& xwin::getXWinState()
{
  return xWinState;
}