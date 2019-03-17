#include "Win32Dialogs.h"

namespace xwin
{
void showMessageBox(const MessageDesc& mdesc)
{

    UINT flags = MB_APPLMODAL | MB_SETFOREGROUND | MB_ICONINFORMATION;
    flags |= MB_OK;
    //auto result = MessageBox(nullptr, L"Text", L"Title", flags);
}

void showOpenDialog(const OpenSaveDialogDesc& odesc) {}

void showSaveDialog(const OpenSaveDialogDesc& sdesc) {}
}