#include "NoopWindow.h"

namespace xwin
{
NoopWindow::~NoopWindow() { close(); }

bool NoopWindow::create(WindowDesc& desc, EventQueue& eventQueue,
                        Window* parent)
{
    return true;
}
void NoopWindow::showMouse(bool show) {}

void NoopWindow::close() {}

void NoopWindow::setWindowSize(unsigned x, unsigned y) {}

void NoopWindow::setMousePosition(unsigned x, unsigned y) {}

UVec2 NoopWindow::getCurrentDisplaySize() { return UVec2(0, 0); }

}