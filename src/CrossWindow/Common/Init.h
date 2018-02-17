#pragma once

#include "Macros.h"
#include "State.h"

namespace xwin
{
    bool init(MainArgs);

    XWinState& getXWinState();
}