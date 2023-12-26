#pragma once

#include <Windows.h>
#include <dwmapi.h>

#if defined(__MINGW32__)
    typedef WINBOOL (WINAPI *DwmDefWindowProcFunc)(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam, LRESULT *plResult);
    typedef HRESULT (WINAPI *DwmEnableBlurBehindWindowFunc)(HWND hWnd, const DWM_BLURBEHIND *pBlurBehind);
    typedef HRESULT (WINAPI *DwmEnableCompositionFunc)(UINT uCompositionAction);
    typedef HRESULT (WINAPI *DwmEnableMMCSSFunc)(WINBOOL fEnableMMCSS);
    typedef HRESULT (WINAPI *DwmExtendFrameIntoClientAreaFunc)(HWND hWnd, const MARGINS *pMarInset);
    typedef HRESULT (WINAPI *DwmGetColorizationColorFunc)(DWORD *pcrColorization, WINBOOL *pfOpaqueBlend);
    typedef HRESULT (WINAPI *DwmGetCompositionTimingInfoFunc)(HWND hwnd, DWM_TIMING_INFO* pTimingInfo);
    typedef HRESULT (WINAPI *DwmGetWindowAttributeFunc)(HWND hwnd, DWORD dwAttribute, PVOID pvAttribute, DWORD cbAttribute);
    typedef HRESULT (WINAPI *DwmIsCompositionEnabledFunc)(BOOL* pfEnabled);
    typedef HRESULT (WINAPI *DwmModifyPreviousDxFrameDurationFunc)(HWND hwnd, INT cRefreshes, BOOL fRelative);
    typedef HRESULT (WINAPI *DwmQueryThumbnailSourceSizeFunc)(HTHUMBNAIL hThumbnail, PSIZE pSize);
    typedef HRESULT (WINAPI *DwmRegisterThumbnailFunc)(HWND hwndDestination, HWND hwndSource, PHTHUMBNAIL phThumbnailId);
    typedef HRESULT (WINAPI *DwmSetDxFrameDurationFunc)(HWND hwnd, INT cRefreshes);
    typedef HRESULT (WINAPI *DwmSetPresentParametersFunc)(HWND hwnd, DWM_PRESENT_PARAMETERS *pPresentParams);
    typedef HRESULT (WINAPI *DwmSetWindowAttributeFunc)(HWND hwnd, DWORD dwAttribute, LPCVOID pvAttribute, DWORD cbAttribute);
    typedef HRESULT (WINAPI *DwmUnregisterThumbnailFunc)(HTHUMBNAIL hThumbnailId);
    typedef HRESULT (WINAPI *DwmUpdateThumbnailPropertiesFunc)(HTHUMBNAIL hThumbnailId, const DWM_THUMBNAIL_PROPERTIES *ptnProperties);
    typedef HRESULT (WINAPI *DwmAttachMilContentFunc)(HWND hwnd);
    typedef HRESULT (WINAPI *DwmDetachMilContentFunc)(HWND hwnd);
    typedef HRESULT (WINAPI *DwmFlushFunc)(void);
    typedef HRESULT (WINAPI *DwmGetGraphicsStreamTransformHintFunc)(UINT uIndex, MilMatrix3x2D *pTransform);
    typedef HRESULT (WINAPI *DwmGetGraphicsStreamClientFunc)(UINT uIndex, UUID *pClientUuid);
    typedef HRESULT (WINAPI *DwmGetTransportAttributesFunc)(BOOL *pfIsRemoting, BOOL *pfIsConnected, DWORD *pDwGeneration);
    typedef HRESULT (WINAPI *DwmTransitionOwnedWindowFunc)(HWND hwnd, DWMTRANSITION_OWNEDWINDOW_TARGET target);

// Windows 7
#if _WIN32_WINNT >= 0x0601
    typedef HRESULT (WINAPI *DwmSetIconicThumbnailFunc)(HWND hwnd, HBITMAP hbmp, DWORD dwSITFlags);
    typedef HRESULT (WINAPI *DwmSetIconicLivePreviewBitmapFunc)(HWND hwnd, HBITMAP hbmp, POINT *pptClient, DWORD dwSITFlags);
    typedef HRESULT (WINAPI *DwmInvalidateIconicBitmapsFunc)(HWND hwnd);
#endif

    extern "C" DwmDefWindowProcFunc                    pDwmDefWindowProc;
    extern "C" DwmEnableBlurBehindWindowFunc           pDwmEnableBlurBehindWindow;
    extern "C" DwmEnableCompositionFunc                pDwmEnableComposition;
    extern "C" DwmEnableMMCSSFunc                      pDwmEnableMMCSS;
    extern "C" DwmExtendFrameIntoClientAreaFunc        pDwmExtendFrameIntoClientArea;
    extern "C" DwmGetColorizationColorFunc             pDwmGetColorizationColor;
    extern "C" DwmGetCompositionTimingInfoFunc         pDwmGetCompositionTimingInfo;
    extern "C" DwmGetWindowAttributeFunc               pDwmGetWindowAttribute;
    extern "C" DwmIsCompositionEnabledFunc             pDwmIsCompositionEnabled;
    extern "C" DwmModifyPreviousDxFrameDurationFunc    pDwmModifyPreviousDxFrameDuration;
    extern "C" DwmQueryThumbnailSourceSizeFunc         pDwmQueryThumbnailSourceSize;
    extern "C" DwmRegisterThumbnailFunc                pDwmRegisterThumbnail;
    extern "C" DwmSetDxFrameDurationFunc               pDwmSetDxFrameDuration;
    extern "C" DwmSetPresentParametersFunc             pDwmSetPresentParameters;
    extern "C" DwmSetWindowAttributeFunc               pDwmSetWindowAttribute;
    extern "C" DwmUnregisterThumbnailFunc              pDwmUnregisterThumbnail;
    extern "C" DwmUpdateThumbnailPropertiesFunc        pDwmUpdateThumbnailProperties;
    extern "C" DwmAttachMilContentFunc                 pDwmAttachMilContent;
    extern "C" DwmDetachMilContentFunc                 pDwmDetachMilContent;
    extern "C" DwmFlushFunc                            pDwmFlush;
    extern "C" DwmGetGraphicsStreamTransformHintFunc   pDwmGetGraphicsStreamTransformHint;
    extern "C" DwmGetGraphicsStreamClientFunc          pDwmGetGraphicsStreamClient;
    extern "C" DwmGetTransportAttributesFunc           pDwmGetTransportAttributes;
    extern "C" DwmTransitionOwnedWindowFunc            pDwmTransitionOwnedWindow;

// Windows 7
#if _WIN32_WINNT >= 0x0601
    extern "C" DwmSetIconicThumbnailFunc               pDwmSetIconicThumbnail;
    extern "C" DwmSetIconicLivePreviewBitmapFunc       pDwmSetIconicLivePreviewBitmap;
    extern "C" DwmInvalidateIconicBitmapsFunc          pDwmInvalidateIconicBitmaps;
#endif

    struct LoadDWMAPI {
        LoadDWMAPI();
        ~LoadDWMAPI();

        HMODULE hDwmapi = nullptr;
    };

    #define DwmDefWindowProc                        pDwmDefWindowProc
    #define DwmEnableBlurBehindWindow               pDwmEnableBlurBehindWindow
    #define DwmEnableComposition                    pDwmEnableComposition
    #define DwmEnableMMCSS                          pDwmEnableMMCSS
    #define DwmExtendFrameIntoClientArea            pDwmExtendFrameIntoClientArea
    #define DwmGetColorizationColor                 pDwmGetColorizationColor
    #define DwmGetCompositionTimingInfo             pDwmGetCompositionTimingInfo
    #define DwmGetWindowAttribute                   pDwmGetWindowAttribute
    #define DwmIsCompositionEnabled                 pDwmIsCompositionEnabled
    #define DwmModifyPreviousDxFrameDuration        pDwmModifyPreviousDxFrameDuration
    #define DwmQueryThumbnailSourceSize             pDwmQueryThumbnailSourceSize
    #define DwmRegisterThumbnail                    pDwmRegisterThumbnail
    #define DwmSetDxFrameDuration                   pDwmSetDxFrameDuration
    #define DwmSetPresentParameters                 pDwmSetPresentParameters
    #define DwmSetWindowAttribute                   pDwmSetWindowAttribute
    #define DwmUnregisterThumbnail                  pDwmUnregisterThumbnail
    #define DwmUpdateThumbnailProperties            pDwmUpdateThumbnailProperties
    #define DwmAttachMilContent                     pDwmAttachMilContent
    #define DwmDetachMilContent                     pDwmDetachMilContent
    #define DwmFlush                                pDwmFlush
    #define DwmGetGraphicsStreamTransformHint       pDwmGetGraphicsStreamTransformHint
    #define DwmGetGraphicsStreamClient              pDwmGetGraphicsStreamClient
    #define DwmGetTransportAttributes               pDwmGetTransportAttributes
    #define DwmTransitionOwnedWindow                pDwmTransitionOwnedWindow

// Windows 7
#if _WIN32_WINNT >= 0x0601
    #define DwmSetIconicThumbnail                   pDwmSetIconicThumbnail
    #define DwmSetIconicLivePreviewBitmap           pDwmSetIconicLivePreviewBitmap
    #define DwmInvalidateIconicBitmaps              pDwmInvalidateIconicBitmaps
#endif

#endif  // __MINGW32__
