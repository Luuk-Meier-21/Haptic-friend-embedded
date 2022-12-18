#include "/Users/luukmeier/Documents/Repos/Haptic Friend/arduino/src/HFKeyboard/HFKeyboard.h"
#include "/Users/luukmeier/Documents/Repos/Haptic Friend/arduino/src/HFButton/HFButton.h"
#include "/Users/luukmeier/Documents/Repos/Haptic Friend/arduino/src/SerialController/SerialController.h"

HFKeyboard keyboard;
SerialController serialController;

InputNode node;

void setup() {
    Serial.begin(57600); // 57600 is the max, higher values will not work.
    while (!Serial) { ; } // wait for serial port to connect. Needed for native USB

    serialController.setEventListener(SerialController::Instruction, onInstruction);
    serialController.setEventListener(SerialController::Setter, onSetter);

    keyboard.addNode('a', 4, 5);
    keyboard.addNode('b', 5, 10);
    keyboard.addNode('c', 6, 20);
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
//      g<node: char?>  

// i:   Input message:
//      i<node: char><value: int>

void onInstruction(String data) {
    Serial.println("Instruction: " + data);
}

void onSetter(String data) {
    Serial.println("Setter: "+ data);
}