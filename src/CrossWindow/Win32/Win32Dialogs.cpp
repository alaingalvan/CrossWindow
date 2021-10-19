#include "Win32Dialogs.h"
#include "../Common/Dialogs.h"

namespace xwin
{

// https://docs.microsoft.com/en-us/windows/desktop/learnwin32/example--the-open-dialog-box

void showMessageBox(const MessageDesc& mdesc)
{

    UINT flags = MB_APPLMODAL | MB_SETFOREGROUND | MB_ICONINFORMATION;
    flags |= MB_OK;
    MessageBox(nullptr, "Text", "Title", flags);
}

bool showOpenDialog(const OpenSaveDialogDesc& odesc, std::string& outPath)
{
    bool success = false;
    HRESULT hr =
        CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
    if (SUCCEEDED(hr))
    {
        IFileOpenDialog* pFileOpen;

        // Create the FileOpenDialog object.
        hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_ALL,
                              IID_IFileOpenDialog,
                              reinterpret_cast<void**>(&pFileOpen));

        if (SUCCEEDED(hr))
        {
            // Show the Open dialog box.
            std::wstring title =
                std::wstring(odesc.title.begin(), odesc.title.end());
            pFileOpen->SetTitle(title.c_str());
            std::wstring okLabel =
                std::wstring(odesc.okLabel.begin(), odesc.okLabel.end());
            if (!okLabel.empty())
            {
                pFileOpen->SetOkButtonLabel(okLabel.c_str());
            }
            if (!odesc.filters.empty())
            {
                // pFileOpen->SetDefaultExtension(L".obj"); // TODO: Should this
                // be accessable?

                // Convert filters to wstring
                std::vector<std::pair<std::wstring, std::wstring>> filters;
                for (const std::pair<std::string, std::vector<std::string>>&
                         pa : odesc.filters)
                {
                    std::wstring spec = L"";
                    for (size_t i = 0; i < pa.second.size(); ++i)
                    {
                        const std::string& s = pa.second[i];
                        spec += L"*.";
                        spec += std::wstring(s.begin(), s.end());
                        if (i < pa.second.size() - 1)
                        {
                            spec += L";";
                        }
                    }
                    filters.emplace_back(
                        std::wstring(pa.first.begin(), pa.first.end()), spec);
                }

                std::vector<COMDLG_FILTERSPEC> specs;
                specs.resize(filters.size());
                for (size_t i = 0; i < filters.size(); ++i)
                {
                    COMDLG_FILTERSPEC spec;
                    spec.pszName = filters[i].first.c_str();
                    spec.pszSpec = filters[i].second.c_str();
                    specs[i] = spec;
                }
                pFileOpen->SetFileTypes(static_cast<UINT>(specs.size()),
                                        specs.data());
            }
            FILEOPENDIALOGOPTIONS opts;
            opts = pFileOpen->GetOptions(&opts);
            if (odesc.openFolders)
            {
                pFileOpen->SetOptions(opts | FOS_PICKFOLDERS);
            }
            hr = pFileOpen->Show(NULL);

            // Get the file name from the dialog box.
            if (SUCCEEDED(hr))
            {
                IShellItem* pItem;
                hr = pFileOpen->GetResult(&pItem);
                if (SUCCEEDED(hr))
                {
                    PWSTR pszFilePath = L"";
                    hr = pItem->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);
                    std::wstring outPathW = pszFilePath;
                    std::string op =
                        std::string(outPathW.begin(), outPathW.end());
                    outPath = op;
                    success = true;

                    pItem->Release();
                }
            }
            pFileOpen->Release();
        }
        CoUninitialize();
    }
    return success;
}

bool showSaveDialog(const OpenSaveDialogDesc& sdesc, std::string& outPath)
{
    bool success = false;
    HRESULT hr =
        CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
    if (SUCCEEDED(hr))
    {
        IFileSaveDialog* pFileSave;
        // Create the FileOpenDialog object.
        hr = CoCreateInstance(CLSID_FileSaveDialog, NULL, CLSCTX_ALL,
                              IID_IFileSaveDialog,
                              reinterpret_cast<void**>(&pFileSave));

        if (SUCCEEDED(hr))
        {
            // Show the Open dialog box.
            std::wstring title =
                std::wstring(sdesc.title.begin(), sdesc.title.end());
            pFileSave->SetTitle(title.c_str());
            std::wstring okLabel =
                std::wstring(sdesc.okLabel.begin(), sdesc.okLabel.end());
            if (!okLabel.empty())
            {
                pFileSave->SetOkButtonLabel(okLabel.c_str());
            }
            if (!sdesc.filters.empty())
            {
                // pFileOpen->SetDefaultExtension(L".obj");

                // Convert to wstring
                std::vector<std::pair<std::wstring, std::wstring>> filters;
                for (const std::pair<std::string, std::vector<std::string>>&
                         pa : sdesc.filters)
                {
                    std::wstring spec = L"";
                    for (size_t i = 0; i < pa.second.size(); ++i)
                    {
                        const std::string& s = pa.second[i];
                        spec += L"*.";
                        spec += std::wstring(s.begin(), s.end());
                        if (i < pa.second.size() - 1)
                        {
                            spec += L";";
                        }
                    }
                    filters.emplace_back(
                        std::wstring(pa.first.begin(), pa.first.end()), spec);
                }

                std::vector<COMDLG_FILTERSPEC> specs;
                specs.resize(filters.size());
                for (size_t i = 0; i < filters.size(); ++i)
                {
                    COMDLG_FILTERSPEC spec;
                    spec.pszName = filters[i].first.c_str();
                    spec.pszSpec = filters[i].second.c_str();
                    specs[i] = spec;
                }
                pFileSave->SetFileTypes(static_cast<UINT>(specs.size()),
                                        specs.data());
            }
            hr = pFileSave->Show(NULL);

            // Get the file name from the dialog box.
            if (SUCCEEDED(hr))
            {
                IShellItem* pItem;
                hr = pFileSave->GetResult(&pItem);
                if (SUCCEEDED(hr))
                {
                    PWSTR pszFilePath;
                    hr = pItem->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);
                    std::wstring outPathW = pszFilePath;
                    std::string op =
                        std::string(outPathW.begin(), outPathW.end());
                    outPath = op;
                    success = true;

                    pItem->Release();
                }
            }
            pFileSave->Release();
        }
        CoUninitialize();
    }
    return success;
}
}