#include "gtest/gtest.h"
#include "CrossWindow/CrossWindow.h"

xmain(MainArgs)
{

    // Initialize CrossWindow with main function args
    xwin::init(MainArgsVars);

#ifdef XWIN_WINDOWS
    ShowWindow(GetConsoleWindow(), SW_RESTORE);

    LPWSTR *szArgList;
    int argCount;

    szArgList = CommandLineToArgvW(GetCommandLineW(), &argCount);
    if (szArgList == NULL)
    {
        MessageBox(NULL, "Unable to parse command line", "Error", MB_OK);
        return 10;
    }

    ::testing::InitGoogleTest(&argCount, szArgList);
    RUN_ALL_TESTS();

    LocalFree(szArgList);

    return 0;
#else
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
#endif
}