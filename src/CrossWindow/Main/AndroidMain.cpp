#import "Main.h"
#include "../Common/Init.h"

#include <android/log.h>
#include <android/native_activity.h>
#include <android/asset_manager.h>
#include <android_native_app_glue.h>

#include "android_util.h"

#include <sys/system_properties.h>

void android_main(android_app* app)
{
    xwin::init(app);

    // Get arguments
    const char key[] = "args";
    char *appTag = (char *)APP_SHORT_NAME;
    int argc = 0;
    char **argv = get_args(app, key, appTag, &argc);

    xmain(argc, (const char**)argv);

    // Free arguments
    for (int i = 0; i < argc; i++) free(argv[i]);
}