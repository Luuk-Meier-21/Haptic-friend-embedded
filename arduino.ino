#include <HFKeyboard.h>
#include <HFButton.h>
#include <SerialController.h>

// Pins
const int exitPin = 12;
const int outputPinA = 5;
const int inputPin = 8;

// Serial reading:
String serialString;

HFButton button = HFButton(inputPin);
HFKeyboard keyboard;

SerialController serialController;

// Message types:
// s:   Setter message, s<node: int><type: char><character: char>
// i:   Input message, i<node: int><value: int>

void pressKey(char key) {
    Serial.println("press");
}

void releaseKey(char key) {
    Serial.println("release");
}

void setup() {
    Serial.begin(57600) ; // 115200 is the max, higher values will not work.
    while (!Serial) {
        ; // wait for serial port to connect. Needed for native USB
    }
    pinMode(outputPinA, OUTPUT);
    pinMode(exitPin, INPUT_PULLUP);
    pinMode(inputPin, INPUT_PULLUP);

    // Keyboard.begin();

    button.attachClick(pressKey, releaseKey, 'a');
}

void loop() {    
    button.tick();
    serialController.tick();
    
    // Serial.println("(" + String(keyboard._nodes.at(0).inputPin) + ")");
}
