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

enum ClickState {
    Press,
    Release
};

void handleClick(uint8_t key, ClickState state) {
    switch (state) {
        case ClickState::Press: Keyboard.press(key); break;
        case ClickState::Release: Keyboard.release(key); break;
    }
};

void handleOptions(const ListenerOptions options, const ClickState state) {   
    if(options.leftShift) handleClick(KEY_LEFT_SHIFT, state);
    if(options.rightShift) handleClick(KEY_RIGHT_SHIFT, state);

    if(options.leftCtrl) handleClick(KEY_LEFT_CTRL, state);
    if(options.rightCtrl) handleClick(KEY_RIGHT_CTRL, state);

    if(options.leftCtrl) handleClick(KEY_LEFT_CTRL, state);
    if(options.rightCtrl) handleClick(KEY_RIGHT_CTRL, state);
};

/**
 * Press any keystroke with 
*/

void pressKeystroke(char keystroke, ListenerOptions options) {
    handleOptions(options, ClickState::Press);
    Keyboard.press(keystroke);
}
void releaseKeystroke(char keystroke, ListenerOptions options) {
    handleOptions(options, ClickState::Release);
    Keyboard.release(keystroke);
}

void pressArrow(char arrowChar, ListenerOptions options) {
    
}
void releaseArrow(char arrowChar, ListenerOptions options) {
    
}

void Listener::attachInteraction() {
    switch (type) {
        case ListenerType::Keystroke:
            node.button.attachClick(pressKeystroke, releaseKeystroke, keystroke, options);
            break;
        case ListenerType::Arrow:
            node.button.attachClick(pressArrow, releaseArrow, keystroke, options);
            break;
        case ListenerType::WASD:
            node.button.attachClick(pressArrow, releaseArrow, keystroke, options);
            break;
    }
}


