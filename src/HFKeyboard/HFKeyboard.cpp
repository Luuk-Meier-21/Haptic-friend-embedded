#include "Arduino.h"
#include "HFKeyboard.h"

HFKeyboard::HFKeyboard() {

};

void HFKeyboard::setup() {

};

void HFKeyboard::tick() {

};

InputNode HFKeyboard::createNode(char id, int inputPin, int outputPin) {
    InputNode node;
    node.id = id;
    node.inputPin = inputPin;
    node.outputPin = outputPin;
    node.valid = true;
    return node;
}

InputNode HFKeyboard::createNode(bool isValid) {
    InputNode node;
    node.id = 'x';
    node.inputPin = 0;
    node.outputPin = 0;
    node.valid = isValid;
    return node;
}

InputNode HFKeyboard::addNode(char id, int inputPin, int outputPin) {
    InputNode node = createNode(id, inputPin, outputPin);
    push(_nodes, _nodesLength, node);
    return node;
};

InputNode HFKeyboard::findNode(char targetId) {
    // Inverse lookup:
    InputNode targetNode;
    for (int i = 0; i < _nodesLength; i++) {
        if(_nodes[i].id == targetId) {
            targetNode = _nodes[i];
            break;
        }
    }
    if(!targetNode.valid) return createNode(false);
    return targetNode;
};

Listener HFKeyboard::createListener(bool isValid) { 
    Listener listener;
    listener.node = createNode(isValid);
    listener.type = 'empty';
    listener.keystroke = NULL;
    listener.valid = isValid;
    return listener;
}

Listener HFKeyboard::createListener(char node, char type, char keystroke) { 
    InputNode targetNode = findNode(node);
    if (!targetNode.valid) return createListener(false);
}

void HFKeyboard::addListener(Listener listener) {
    
};

template <size_t n, class T>
void HFKeyboard::push(T (&arr)[n], int &index, T const value) {
    // static size_t index = 0;

    arr[index] = value;
    index = (index + 1) % n;
}

// template <size_t n, class T> 
// T HFKeyboard::pop(T (&arr)[n]) {
// //   static size_t index = 0;

//   T result = arr[index];
//   index = (index + 1) % n;
//   return result;
// }
