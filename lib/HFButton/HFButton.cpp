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
    int reading = digitalRead(_pin);

	if (reading != _prevState) {
        _lastDebounceTime = millis();
    }

    if ((millis() - _lastDebounceTime) > _debounceDelay) {
        if (reading != _state) _state = reading;
    }

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

	_prevState = reading;
}