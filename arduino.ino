#include <HFKeyboard.h>
#include <HFButton.h>
#include <SerialController.h>

// Pins
const int outputPinA = 5;
const int inputPin = 8;

HFButton button = HFButton(inputPin);

HFKeyboard keyboard;
SerialController serialController;

InputNode node;

// Message types:
// s:   Setter message, sets listeners to given nodes.
//      s<node: char><type: char><character: char>

// g:   Getter message, gets all active nodes, pass node param to check specific node:  
//      g<node: char?>  

// i:   Input message:
//      i<node: char><value: int>

void setup() {
    Serial.begin(57600) ; // 115200 is the max, higher values will not work.
    while (!Serial) { ; } // wait for serial port to connect. Needed for native USB
    pinMode(outputPinA, OUTPUT);

    button.attachClick(pressKey, releaseKey, 'a');

    serialController.setEventListener(SerialController::Instruction, onInstruction);
    serialController.setEventListener(SerialController::Setter, onSetter);

    keyboard.addNode('a', 4, 5);
    keyboard.addNode('b', 5, 10);
    keyboard.addNode('c', 6, 20);
}

void loop() {    
    button.tick();
    serialController.tick();
    keyboard.tick();
}

void onInstruction(String data) {
    Serial.println("Instruction: " + data);
}

void onSetter(String data) {
    Serial.println("Setter: "+ data);
}

void pressKey(char key) {
    Serial.println("press");
}

void releaseKey(char key) {
    Serial.println("release");
}