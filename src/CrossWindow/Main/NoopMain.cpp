#include "../Common/Init.h"
#include "Main.h"

int main(int argc, char** argv)
{
    xwin::init(argc, argv);
    xmain(argc, argv);
    return 0;
}