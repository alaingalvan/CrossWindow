#pragma once

#include "DialogsDesc.h"

namespace xwin
{

void showMessageBox(const MessageDesc& mdesc);

void showOpenDialog(const OpenSaveDialogDesc& odesc);

void showSaveDialog(const OpenSaveDialogDesc& sdesc);
}