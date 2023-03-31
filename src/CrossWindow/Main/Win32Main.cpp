#include "../Common/Init.h"
#include "Main.h"
#include <stdio.h>

INT WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,
                   _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
#ifdef _DEBUG
    AllocConsole();
    FILE* pCout = nullptr;
    FILE* pCerr = nullptr;
    freopen_s(&pCout, "CONOUT$", "w+", stdout);
    freopen_s(&pCerr, "CONOUT$", "w+", stderr);
#endif

    // Setup command line arguments.
    int argc = 0;
    char** argv = 0;

    // Use the CommandLine functions to get the command line arguments,
    // and convert w_char to utf8 chars.
    LPWSTR* commandLineArgs = CommandLineToArgvW(GetCommandLineW(), &argc);
    if (NULL == commandLineArgs)
    {
        argc = 0;
    }

    if (argc > 0)
    {
        argv = (char**)malloc(sizeof(char*) * argc);
        if (argv == NULL)
        {
            argc = 0;
        }
        else
        {
            for (int iii = 0; iii < argc; iii++)
            {
                size_t wideCharLen = wcslen(commandLineArgs[iii]);
                size_t numConverted = 0;

                argv[iii] = (char*)malloc(sizeof(char) * (wideCharLen + 1));
                if (argv[iii] != NULL)
                {
                    wcstombs_s(&numConverted, argv[iii], wideCharLen + 1,
                               commandLineArgs[iii], wideCharLen + 1);
                }
            }
        }
    }
    else
    {
        argv = NULL;
    }

    xwin::init(hInstance, hPrevInstance, lpCmdLine, nCmdShow);
    xmain(argc, (const char**)argv);

    // Free up the items we had to allocate for the command line arguments.
    if (argc > 0 && argv != NULL)
    {
        for (int iii = 0; iii < argc; iii++)
        {
            char* arg = argv[iii];
            if (arg != NULL)
            {
                free(argv[iii]);
            }
        }
        free(argv);
    }

#ifdef _DEBUG
    FreeConsole();
    if (pCout != nullptr) fclose(pCout);
    if (pCerr != nullptr) fclose(pCerr);
#endif

    return 0;
}
