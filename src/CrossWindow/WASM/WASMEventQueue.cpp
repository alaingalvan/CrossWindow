#include "WASMEventQueue.h"
#include "CrossWindow/Common/Event.h"
#include <emscripten/em_types.h>
#include <emscripten/html5.h>

namespace xwin
{

EM_BOOL mouseCallback(int eventType, const EmscriptenMouseEvent *mouseEvent, void *userData)
{
    ButtonState btnState{ButtonState::ButtonStateMax};
    MouseInput btnInput{MouseInput::MouseInputMax};
    std::queue<Event>* evtQueue = static_cast<std::queue<Event>*>(userData);

    switch (eventType)
    {

    case EMSCRIPTEN_EVENT_MOUSEDOWN:
        btnState = ButtonState::Pressed;
        break;

    case EMSCRIPTEN_EVENT_MOUSEUP:
        btnState = ButtonState::Released;
        break;

    default:
        ;
    }

    if(btnState != ButtonStateMax)
    {
        btnInput = mouseEvent->button==0 ? MouseInput::Left : mouseEvent->button==1 ? MouseInput::Middle : MouseInput::Right;
        MouseInputData mid(btnInput, btnState, ModifierState());
        evtQueue->emplace(mid);
    }
    else
    {
        MouseMoveData mvd(mouseEvent->targetX, mouseEvent->targetY,
                          mouseEvent->screenX, mouseEvent->screenY,
                          mouseEvent->movementX, mouseEvent->movementY);
        evtQueue->emplace(mvd);
    }

    return EM_TRUE;
}

EventQueue::EventQueue()
{
    emscripten_set_keydown_callback("#canvas", 0, 1, keyCallback);
    emscripten_set_keyup_callback("#canvas", 0, 1, keyCallback);
    emscripten_set_keypress_callback("#canvas", 0, 1, keyCallback);

    emscripten_set_mousedown_callback("#canvas", &mQueue, 1, mouseCallback);
    emscripten_set_mouseup_callback("#canvas", &mQueue, 1, mouseCallback);
    emscripten_set_mousemove_callback("#canvas", &mQueue, 1, mouseCallback);
}

void EventQueue::update() {}

bool EventQueue::empty() { return mQueue.empty(); }

const Event& EventQueue::front() { return mQueue.front(); }

void EventQueue::pop() { mQueue.pop(); }

EM_BOOL EventQueue::keyCallback(int eventType, const EmscriptenKeyboardEvent* e, void* userData)
{
    int dom_pk_code = emscripten_compute_dom_pk_code(e->code);

    //    dom_pk_code;
    //    e->location;
    //    e->ctrlKey;
    //    e->shiftKey;
    //    e->altKey;
    //    e->metaKey;
    //    e->repeat;
    //    e->locale;
    //    e->charValue;
    //    e->charCode;
    //    e->keyCode;
    //    e->keyCode;
    //    e->which;

    //    eventType == EMSCRIPTEN_EVENT_KEYUP;

    // Return true for events we want to suppress default web browser handling
    // for. For testing purposes, want to return false here on most KeyDown
    // messages so that they get transformed to KeyPress messages.
    bool supressEvent =
        e->keyCode == DOM_VK_BACK_SPACE // Don't navigate away from this test
        // page on backspace.
        || e->keyCode == DOM_VK_TAB // Don't change keyboard focus to different
        // browser UI elements while testing.
        ||
        (e->keyCode >= DOM_VK_F1 &&
         e->keyCode <= DOM_VK_F24) // Don't F5 refresh the test page to reload.
        || e->ctrlKey // Don't trigger e.g. Ctrl-B to open bookmarks
        || e->altKey  // Don't trigger any alt-X based shortcuts either (Alt-F4
        // is not overrideable though)
        || eventType == EMSCRIPTEN_EVENT_KEYPRESS ||
        eventType == EMSCRIPTEN_EVENT_KEYUP; // Don't perform any default
        // actions on these.

    return supressEvent;
}

}
