#include "HFKeyboard.h"

Node::Node(char _id, int _inputPin, int _outputPin) {
    id = _id;
    inputPin = _inputPin;
    outputPin = _outputPin;
    valid = true;
    button = HFButton(_inputPin);
};

Node::Node() {
    id = 'z';
    inputPin = NULL;
    outputPin = NULL;
    valid = false;
};