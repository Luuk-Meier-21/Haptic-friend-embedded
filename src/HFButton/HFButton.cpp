#include "Arduino.h"
#include "HFButton.h"

HFButton::HFButton(int pin) {
	pinMode(pin, INPUT_PULLUP);
	_pin = pin;
}

// Void functions:
void HFButton::attachPress(callbackFunction newFunction) {
	_pressFunc = newFunction;
}

void HFButton::attachRelease(callbackFunction newFunction) {
	_releaseFunc = newFunction;
}

// Param functions:
void HFButton::attachPress(keyboardFunction newFunction, char param) {
	_paramPressFunc = newFunction;
    _keyboardParam = param;
}

void HFButton::attachRelease(keyboardFunction newFunction, char param) {
	_paramReleaseFunc = newFunction;
    _keyboardParam = param;
}

void HFButton::attachClick(callbackFunction pressFunction, callbackFunction releaseFunction) {
    _pressFunc = releaseFunction;
	_releaseFunc = releaseFunction;
}

void HFButton::attachClick(keyboardFunction pressFunction, keyboardFunction releaseFunction, char param) {
    _paramPressFunc = pressFunction;
	_paramReleaseFunc = releaseFunction;
    _keyboardParam = param;
}

void HFButton::tick() {
    // get current reading.
    int reading = digitalRead(_pin);

    // check if reading is the same as _prevState (reading from last tick call).
	if (reading != _prevState) {
        // set to current time.
        _lastDebounceTime = millis();
    }

    // check if current time - last debounce time is higher then debounce delay.
    if ((millis() - _lastDebounceTime) > _debounceDelay) {
        // check if reading is different than the reading made x seconds back.
        // if true set the _state.
        if (reading != _state) _state = reading;
    }

    // handle debounce safe state:
	if (_state == LOW && !_wasPressed) {
        // on first press:
        if (_pressFunc) _pressFunc();
        if (_paramPressFunc) _paramPressFunc(_keyboardParam);
        _wasPressed = true;
    }
    else if (_state == HIGH && _wasPressed) {
        // on release:
        if (_releaseFunc) _releaseFunc();
        if (_paramReleaseFunc) _paramReleaseFunc(_keyboardParam);
        _wasPressed = false;
    }

    // set prev state:
	_prevState = reading;
}