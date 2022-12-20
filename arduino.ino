#include "/Users/luukmeier/Documents/Repos/Haptic Friend/arduino/src/HFKeyboard/HFKeyboard.h"
#include "/Users/luukmeier/Documents/Repos/Haptic Friend/arduino/src/HFButton/HFButton.h"
#include "/Users/luukmeier/Documents/Repos/Haptic Friend/arduino/src/SerialController/SerialController.h"

#include <Keyboard.h>

HFKeyboard keyboard;
SerialController serialController;

Node node;

void setup() {
    while (!Serial) { ; } // wait for serial port to connect. Needed for native USB
    Serial.begin(57600); // 57600 is the max, higher values will not work.
    Keyboard.begin();
    serialController.setEventListener(SerialController::Instruction, onInstruction);
    serialController.setEventListener(SerialController::Setter, onSetter);
    serialController.setEventListener(SerialController::Getter, onGetter);
    serialController.setEventListener(SerialController::Flush, onFlush);

    keyboard.addNode('a', 10, 12);
    // keyboard.addNode('b', 5, 10);
    // keyboard.addNode('c', 6, 20);
}

void loop() {    
    // button.tick();
    serialController.tick();
    keyboard.tick();
}

// Message types:
// s:   Setter message, sets listeners to given nodes.
//      s<node: char><type: char><character: char>

// g:   Getter message, gets all active nodes, pass node param to check specific node:  
//      g<type: char><node: char?>  
//      type: n: nodes, l: listeners

// i:   Instruction message, do something with this input.
//      i<node: char><value: int>

/**
 * Function called when the serialport recieves a message with a 's' identifier, for example: "saag".
*/
void onSetter(String data) {
    char identifier = data[0]; // Will always be 's' here.
    char nodeChar = data[1];
    char typeChar = data[2]; // Useless until implemented.
    char keystroke = data[3];
    bool succes = keyboard.addListener(nodeChar, typeChar, keystroke);
}

/**
 * Function called when the serialport recieves a message with a 'g' identifier, for example: "gl".
*/
void onGetter(String data) {
    Serial.println("———");
    char identifier = data[0];
    char type = data[1];

    switch (type) {
        case 'n': keyboard.logNodes();
        case 'l': keyboard.logListeners();
    }
}

void onFlush(String data) {
    
}

/**
 * Function called when the serialport recieves a message with a 'i' identifier, for example: "ia1".
*/
void onInstruction(String data) {
    Serial.println("Instruction: " + data);
} 