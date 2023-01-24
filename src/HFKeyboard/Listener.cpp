#include "HFKeyboard.h"
#include <Keyboard.h>

Listener::Listener(ListenerNode _node, ListenerType _type, char _keystroke, ListenerOptions _options) {
    node = _node;
    type = ListenerType::Keystroke;
    keystroke = _keystroke;
    options = _options;
    valid = true;
    attachInteraction();
}

Listener::Listener() {
    node = ListenerNode();
    type = ListenerType::Empty;
    keystroke = NULL;
    valid = false;
}

ListenerHFButton::Callable press(char keystroke, ListenerOptions options) {

}
ListenerHFButton::Callable release(char keystroke, ListenerOptions options) {
    
}

void Listener::attachInteraction() {

    switch (type) {
        case ListenerType::Keystroke:
            
            // node.button.attachClick(*press, *release, keystroke);
            break;
    }
}


