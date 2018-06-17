#include "WASMEventQueue.h"



namespace xwin
{
    WASMEventQueue::WASMEventQueue()
    {
        emscripten_set_keydown_callback(0, 0, 1, key_callback);
        emscripten_set_keyup_callback(0, 0, 1, key_callback);
        emscripten_set_keypress_callback(0, 0, 1, key_callback);
    }

    void WASMEventQueue::update()
    {
    }

    EM_BOOL WASMEventQueue::keyCallback(int eventType, const EmscriptenKeyboardEvent *e, void *userData)
    {
        int dom_pk_code = emscripten_compute_dom_pk_code(e->code);

        dom_pk_code;
        e->location;
        e->ctrlKey;
        e->shiftKey;
        e->altKey;
        e->metaKey;
        e->repeat;
        e->locale;
        e->charValue;
        e->charCode;
        e->keyCode;
        e->keyCode;
        e->which;

        eventType == EMSCRIPTEN_EVENT_KEYUP;

        // Return true for events we want to suppress default web browser handling for.
        // For testing purposes, want to return false here on most KeyDown messages so that they get transformed to KeyPress messages.
        bool supressEvent = e->keyCode == DOM_VK_BACK_SPACE // Don't navigate away from this test page on backspace.
            || e->keyCode == DOM_VK_TAB // Don't change keyboard focus to different browser UI elements while testing.
            || (e->keyCode >= DOM_VK_F1 && e->keyCode <= DOM_VK_F24) // Don't F5 refresh the test page to reload.
            || e->ctrlKey // Don't trigger e.g. Ctrl-B to open bookmarks
            || e->altKey // Don't trigger any alt-X based shortcuts either (Alt-F4 is not overrideable though)
            || eventType == EMSCRIPTEN_EVENT_KEYPRESS || eventType == EMSCRIPTEN_EVENT_KEYUP; // Don't perform any default actions on these.

        return supressEvent;
    }
}