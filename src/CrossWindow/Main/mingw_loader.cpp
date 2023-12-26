#pragma once

#include "mingw_loader.h"
#include <stdio.h>

#if defined(__MINGW32__)

DwmDefWindowProcFunc                    pDwmDefWindowProc                   = nullptr;
DwmEnableBlurBehindWindowFunc           pDwmEnableBlurBehindWindow          = nullptr;
DwmEnableCompositionFunc                pDwmEnableComposition               = nullptr;
DwmEnableMMCSSFunc                      pDwmEnableMMCSS                     = nullptr;
DwmExtendFrameIntoClientAreaFunc        pDwmExtendFrameIntoClientArea       = nullptr;
DwmGetColorizationColorFunc             pDwmGetColorizationColor            = nullptr;
DwmGetCompositionTimingInfoFunc         pDwmGetCompositionTimingInfo        = nullptr;
DwmGetWindowAttributeFunc               pDwmGetWindowAttribute              = nullptr;
DwmIsCompositionEnabledFunc             pDwmIsCompositionEnabled            = nullptr;
DwmModifyPreviousDxFrameDurationFunc    pDwmModifyPreviousDxFrameDuration   = nullptr;
DwmQueryThumbnailSourceSizeFunc         pDwmQueryThumbnailSourceSize        = nullptr;
DwmRegisterThumbnailFunc                pDwmRegisterThumbnail               = nullptr;
DwmSetDxFrameDurationFunc               pDwmSetDxFrameDuration              = nullptr;
DwmSetPresentParametersFunc             pDwmSetPresentParameters            = nullptr;
DwmSetWindowAttributeFunc               pDwmSetWindowAttribute              = nullptr;
DwmUnregisterThumbnailFunc              pDwmUnregisterThumbnail             = nullptr;
DwmUpdateThumbnailPropertiesFunc        pDwmUpdateThumbnailProperties       = nullptr;
DwmAttachMilContentFunc                 pDwmAttachMilContent                = nullptr;
DwmDetachMilContentFunc                 pDwmDetachMilContent                = nullptr;
DwmFlushFunc                            pDwmFlush                           = nullptr;
DwmGetGraphicsStreamTransformHintFunc   pDwmGetGraphicsStreamTransformHint  = nullptr;
DwmGetGraphicsStreamClientFunc          pDwmGetGraphicsStreamClient         = nullptr;
DwmGetTransportAttributesFunc           pDwmGetTransportAttributes          = nullptr;
DwmTransitionOwnedWindowFunc            pDwmTransitionOwnedWindow           = nullptr;

// Windows 7
#if _WIN32_WINNT >= 0x0601
DwmSetIconicThumbnailFunc               pDwmSetIconicThumbnail              = nullptr;
DwmSetIconicLivePreviewBitmapFunc       pDwmSetIconicLivePreviewBitmap      = nullptr;
DwmInvalidateIconicBitmapsFunc          pDwmInvalidateIconicBitmaps         = nullptr;

#endif

LoadDWMAPI::LoadDWMAPI() {
    hDwmapi = LoadLibrary(TEXT("dwmapi.dll"));
    if (hDwmapi != NULL) {
        fprintf(stdout, "dwmapi loaded\n");
        pDwmDefWindowProc                  = (DwmDefWindowProcFunc)                  GetProcAddress(hDwmapi, "DwmDefWindowProc");
        pDwmEnableBlurBehindWindow         = (DwmEnableBlurBehindWindowFunc)         GetProcAddress(hDwmapi, "DwmEnableBlurBehindWindow");
        pDwmEnableComposition              = (DwmEnableCompositionFunc)              GetProcAddress(hDwmapi, "DwmEnableComposition");
        pDwmEnableMMCSS                    = (DwmEnableMMCSSFunc)                    GetProcAddress(hDwmapi, "DwmEnableMMCSS");
        pDwmExtendFrameIntoClientArea      = (DwmExtendFrameIntoClientAreaFunc)      GetProcAddress(hDwmapi, "DwmExtendFrameIntoClientArea");
        pDwmGetColorizationColor           = (DwmGetColorizationColorFunc)           GetProcAddress(hDwmapi, "DwmGetColorizationColor");
        pDwmGetCompositionTimingInfo       = (DwmGetCompositionTimingInfoFunc)       GetProcAddress(hDwmapi, "DwmGetCompositionTimingInfo");
        pDwmGetWindowAttribute             = (DwmGetWindowAttributeFunc)             GetProcAddress(hDwmapi, "DwmGetWindowAttribute");
        pDwmIsCompositionEnabled           = (DwmIsCompositionEnabledFunc)           GetProcAddress(hDwmapi, "DwmIsCompositionEnabled");
        pDwmModifyPreviousDxFrameDuration  = (DwmModifyPreviousDxFrameDurationFunc)  GetProcAddress(hDwmapi, "DwmModifyPreviousDxFrameDuration");
        pDwmQueryThumbnailSourceSize       = (DwmQueryThumbnailSourceSizeFunc)       GetProcAddress(hDwmapi, "DwmQueryThumbnailSourceSize");
        pDwmRegisterThumbnail              = (DwmRegisterThumbnailFunc)              GetProcAddress(hDwmapi, "DwmRegisterThumbnail");
        pDwmSetDxFrameDuration             = (DwmSetDxFrameDurationFunc)             GetProcAddress(hDwmapi, "DwmSetDxFrameDuration");
        pDwmSetPresentParameters           = (DwmSetPresentParametersFunc)           GetProcAddress(hDwmapi, "DwmSetPresentParameters");
        pDwmSetWindowAttribute             = (DwmSetWindowAttributeFunc)             GetProcAddress(hDwmapi, "DwmSetWindowAttribute");
        pDwmUnregisterThumbnail            = (DwmUnregisterThumbnailFunc)            GetProcAddress(hDwmapi, "DwmUnregisterThumbnail");
        pDwmUpdateThumbnailProperties      = (DwmUpdateThumbnailPropertiesFunc)      GetProcAddress(hDwmapi, "DwmUpdateThumbnailProperties");
        pDwmAttachMilContent               = (DwmAttachMilContentFunc)               GetProcAddress(hDwmapi, "DwmAttachMilContent");
        pDwmDetachMilContent               = (DwmDetachMilContentFunc)               GetProcAddress(hDwmapi, "DwmDetachMilContent");
        pDwmFlush                          = (DwmFlushFunc)                          GetProcAddress(hDwmapi, "DwmFlush");
        pDwmGetGraphicsStreamTransformHint = (DwmGetGraphicsStreamTransformHintFunc) GetProcAddress(hDwmapi, "DwmGetGraphicsStreamTransformHint");
        pDwmGetGraphicsStreamClient        = (DwmGetGraphicsStreamClientFunc)        GetProcAddress(hDwmapi, "DwmGetGraphicsStreamClient");
        pDwmGetTransportAttributes         = (DwmGetTransportAttributesFunc)         GetProcAddress(hDwmapi, "DwmGetTransportAttributes");
        pDwmTransitionOwnedWindow          = (DwmTransitionOwnedWindowFunc)          GetProcAddress(hDwmapi, "DwmTransitionOwnedWindow");

// Windows 7
#if _WIN32_WINNT >= 0x0601
        pDwmSetIconicThumbnail             = (DwmSetIconicThumbnailFunc)             GetProcAddress(hDwmapi, "DwmSetIconicThumbnail");
        pDwmSetIconicLivePreviewBitmap     = (DwmSetIconicLivePreviewBitmapFunc)     GetProcAddress(hDwmapi, "DwmSetIconicLivePreviewBitmap");
        pDwmInvalidateIconicBitmaps        = (DwmInvalidateIconicBitmapsFunc)        GetProcAddress(hDwmapi, "DwmInvalidateIconicBitmaps");
#endif

    }
    else {
        fprintf(stderr, "dwmapi NOT loaded\n");
    }
}

LoadDWMAPI::~LoadDWMAPI() {
    FreeLibrary(hDwmapi);
}

#endif  // __MINGW32__
