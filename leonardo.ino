#include <Keyboard.h>

// Pins
const int exitPin = 12;
const int outputPinA = 5;
const int inputPin = 8;

// Debounce:
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;

// Serial reading:
String readString;
// Button States:
int buttonState;
int prevButtonState = HIGH;
int outputState = LOW;
bool wasPressed = false;

// | Board     |
// | A ————— B |

void setup()
{
    Serial.begin(115200); // 115200 is the max, higher values will not work.
    pinMode(outputPinA, OUTPUT);
    pinMode(exitPin, INPUT_PULLUP);
    pinMode(inputPin, INPUT_PULLUP);

    Keyboard.begin();

    // Completion byte:
    Serial.write("0\n");
}
void loop()
{
    int reading = digitalRead(inputPin);

    if (reading != prevButtonState) {
        lastDebounceTime = millis();
    }

    if ((millis() - lastDebounceTime) > debounceDelay) {
        if (reading != buttonState) buttonState = reading;
    }

    // Use state:
    if (buttonState == LOW && !wasPressed)
    {
        // on first press:
        digitalWrite(outputPinA, HIGH);
        Keyboard.press('a');
        Serial.write("ON ");
        wasPressed = true;
    }
    else if (buttonState == HIGH && wasPressed)
    {
        // on release:
        digitalWrite(outputPinA, LOW);
        Keyboard.release('a');
        Serial.write("OFF ");
        wasPressed = false;
    }

    // Debugging reset:
    if (digitalRead(exitPin) == LOW)
    {
        digitalWrite(outputPinA, LOW);
        Keyboard.releaseAll();
    }

    prevButtonState = reading;
}
