#ifndef HFButton_h
#define HFButton_h

#include <Arduino.h>

extern "C" {
    typedef void (*callbackFunction)(void);
    typedef void (*keyboardFunction)(char);
    typedef void (*parameterizedCallbackFunction)(void *);
}

class HFButton {
    public:
        HFButton(int pin);
        void tick();

        void attachPress(callbackFunction newFunction);
        void attachPress(keyboardFunction newFunction, char param);
        void attachRelease(callbackFunction newFunction); 
        void attachRelease(keyboardFunction newFunction, char param);
        void attachClick(callbackFunction pressFunction, callbackFunction releaseFunction);
        void attachClick(keyboardFunction pressFunction, keyboardFunction releaseFunction, char param);
        // void attachPress(parameterizedCallbackFunction newFunction, void *parameter);
    private:
        int _pin;
        int _state = HIGH;
        int _prevState = HIGH;
        bool _wasPressed = false;
        unsigned long _lastDebounceTime = 0; 
        unsigned long _debounceDelay = 50;

        callbackFunction _pressFunc = NULL;
        callbackFunction _releaseFunc = NULL;

        keyboardFunction _paramPressFunc = NULL;
        keyboardFunction _paramReleaseFunc = NULL;
        char _keyboardParam;
};
#endif