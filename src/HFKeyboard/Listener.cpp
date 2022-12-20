#include "HFKeyboard.h"
#include <Keyboard.h>

Listener::Listener(Node _node, ListenerType _type, char _keystroke) {
    node = _node;
    type = ListenerType::KeystrokeClick;
    keystroke = _keystroke;
    valid = true;
    attachInteraction();
}

Listener::Listener() {
    node = Node();
    type = ListenerType::Empty;
    keystroke = NULL;
    valid = false;
}

void pressFunc(char keystroke) {
    Keyboard.press(keystroke);
};

void releaseFunc(char keystroke) {
    Keyboard.release(keystroke);
};

void Listener::attachInteraction() {

    switch (type) {
        case ListenerType::KeystrokeClick:
            node.button.attachClick(pressFunc, releaseFunc, keystroke);
            break;
    }
}

