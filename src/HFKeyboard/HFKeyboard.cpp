#include "Arduino.h"
#include "HFKeyboard.h"

HFKeyboard::HFKeyboard() {

};

void HFKeyboard::setup() {

};

void HFKeyboard::tick() {
    for (int i = 0; i < _listenersLength; i++) {
        _listeners[i].node.button.tick();
    }
};

ListenerNode HFKeyboard::defineNode(char id, int inputPin, int outputPin) {
    ListenerNode node = ListenerNode(id, inputPin, outputPin);
    push(_nodes, _nodesLength, node);

    return node;
};

ListenerNode HFKeyboard::findNode(char targetId) {
    // Inverse lookup:
    ListenerNode targetNode;

    for (int i = 0; i < _nodesLength; i++) {
        if(_nodes[i].id == targetId) {
            targetNode = _nodes[i];
            break;
        }
    }
    if(!targetNode.valid) return ListenerNode();
    return targetNode;
};

void HFKeyboard::logNodes() {
    for (int i = 0; i < _nodesLength; i++) {
        Serial.println(_nodes[i].id);
    }
}

bool HFKeyboard::addListener(char nodeChar, char typeChar, char keystroke, String optionsString) {
    ListenerNode targetNode = findNode(nodeChar);
    if (!targetNode.valid) return false;

    ListenerType type = getListenerType(typeChar);
    if (type == Empty) return false;
    
    ListenerOptions options = getListenerOptions(optionsString);

    Listener newListener(targetNode, type, keystroke, options);

    int targetIndex = findListenerIndex(nodeChar);
    if (targetIndex > -1) {
        // If node is taken, replace listener of node with newListener:
        _listeners[targetIndex] = newListener;
        return true;
    } else {
        // No taken node found, push newListener to array:
        push(_listeners, _listenersLength, newListener);
        return true;
    }
};

ListenerOptions HFKeyboard::getListenerOptions(String optionsString) {
    ListenerOptions options;
    for (int i = 0; i < optionsString.length(); i++) {
        char option = optionsString[i];
        switch (option) {
            case 'a': options.leftShift = true; break;
            case 'b': options.rightCtrl = true; break;
            case 'c': options.leftCtrl = true; break;
            case 'd': options.rightCtrl = true; break;
        }
    };
    return options;
}

ListenerType HFKeyboard::getListenerType(char typeChar) {
    switch (typeChar) {
        case 'a': return ListenerType::Keystroke;
        case 'b': return ListenerType::Arrow;
        case 'c': return ListenerType::WASD;
        default: return ListenerType::Empty;
    }
}

int HFKeyboard::findListenerIndex(char targetNodeChar) {
    // Inverse lookup, to generic function?:
    int targetListenerIndex = -1;
    for (int i = 0; i < _listenersLength; i++) {
        if(_listeners[i].node.id == targetNodeChar) {
            targetListenerIndex = i;
            break;
        }
    }
    
    return targetListenerIndex;
};

Listener HFKeyboard::findListener(char targetNodeChar) {
    // Inverse lookup, to generic function?:
    Listener targetListener;
    for (int i = 0; i < _listenersLength; i++) {
        if(_listeners[i].node.id == targetNodeChar) {
            targetListener = _listeners[i];
            break;
        }
    }
    if(!targetListener.valid) return Listener();
    return targetListener;
};

void HFKeyboard::logListeners() {
    for (int i = 0; i < _listenersLength; i++) {
        Serial.println(_listeners[i].node.id);
    }
}

void HFKeyboard::clearListeners() {
  
}


// https://codescracker.com/cpp/program/cpp-program-delete-element-from-array.htm#:~:text=In%20C%2B%2B%2C%20delete%20an,and%20delete%20it%20if%20found.
void HFKeyboard::clearListener(int index) {
    // _listeners[index];
}

template <size_t n, class T>
void HFKeyboard::push(T (&arr)[n], int &length, T const value) {
    // static size_t index = 0;

    arr[length] = value;
    length = (length + 1) % n;
}

// template <size_t n, class T> 
// T HFKeyboard::pop(T (&arr)[n]) {
// //   static size_t index = 0;

//   T result = arr[index];
//   index = (index + 1) % n;
//   return result;
// }
