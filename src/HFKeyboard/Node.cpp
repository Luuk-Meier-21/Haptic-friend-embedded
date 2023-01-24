#include "HFKeyboard.h"

template<class PT, class OT>
Node<PT, OT>::Node(char _id, int _inputPin, int _outputPin) {
    id = _id;
    inputPin = _inputPin;
    outputPin = _outputPin;
    valid = true;
    button = HFButton<PT, OT>(_inputPin);
    pinMode(outputPin, OUTPUT);
};

template<class PT, class OT>
Node<PT, OT>::Node() {
    id = 'z';
    inputPin = NULL;
    outputPin = NULL;
    valid = false;
};

// Solved Bug: undefined reference to Node<char, ListenerOptions>.
// The compiler is not aware of all posible template combiniations telling the compiler what templates to use
// solves this issue. More at:
// https://stackoverflow.com/questions/8752837/undefined-reference-to-template-class-constructor

// Reference fix:
template class Node<char, ListenerOptions>;
