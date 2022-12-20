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

Node HFKeyboard::addNode(char id, int inputPin, int outputPin) {
    Node node = Node(id, inputPin, outputPin);
    push(_nodes, _nodesLength, node);

    return node;
};

Node HFKeyboard::findNode(char targetId) {
    // Inverse lookup:
    Node targetNode;

    for (int i = 0; i < _nodesLength; i++) {
        if(_nodes[i].id == targetId) {
            targetNode = _nodes[i];
            break;
        }
    }
    if(!targetNode.valid) return Node();
    return targetNode;
};

void HFKeyboard::logNodes() {
    for (int i = 0; i < _nodesLength; i++) {
        Serial.println(_nodes[i].id);
    }
}

bool HFKeyboard::addListener(char nodeChar, char type, char keystroke) {
    Node targetNode = findNode(nodeChar);

    if (!targetNode.valid) return false;
    if (findListener(nodeChar).valid) return false;

    Listener listener(targetNode, ListenerType::KeystrokeClick, keystroke);
    
    push(_listeners, _listenersLength, listener);
    return true;
};

int HFKeyboard::findListenerIndex(char targetNodeChar) {
    // Inverse lookup, to generic function?:
    int targetListenerIndex;
    bool found;
    for (int i = 0; i < _listenersLength; i++) {
        if(_listeners[i].node.id == targetNodeChar) {
            targetListenerIndex = i;
            found = true;
            break;
        }
    }
    if(!found) return _listenersLength;
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
        Serial.println(_listeners[i].keystroke);
    }
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
