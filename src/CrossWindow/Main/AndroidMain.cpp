#import "Main.h"
#include "../Common/Init.h"

#include <android/log.h>
#include <android/native_activity.h>
#include <android/asset_manager.h>
#include <android_native_app_glue.h>

#include "android_util.h"

#include <sys/system_properties.h>

void android_main(android_app* state)
{
    xwin::init(state);
    xmain(0, nullptr);
}