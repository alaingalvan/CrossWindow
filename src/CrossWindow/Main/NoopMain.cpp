#include "../Common/Init.h"
#include "Main.h"

int main(int argc, char** argv)
{
    xwin::init(argc, (const char**)argv);
    xmain(argc, (const char**)argv);
    return 0;
}