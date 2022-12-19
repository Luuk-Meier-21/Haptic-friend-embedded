#include "HFKeyboard.h"

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
    Serial.println(keystroke);
};

void releaseFunc(char keystroke) {
    Serial.println(keystroke);
};

void Listener::attachInteraction() {
    keyboardFunction press = pressFunc;

    switch (type) {
        case ListenerType::KeystrokeClick:
            node.button.attachClick(pressFunc, releaseFunc, keystroke);
            break;
    }
}

