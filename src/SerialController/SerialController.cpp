#include "Arduino.h"
#include "SerialController.h"


/**
 * Tick function, call from arduino's loop func.
*/
void SerialController::tick() {
    while (Serial.available()) {
        delay(10);
        char c = Serial.read();
        _currentData += c;
    }
    
    // Use Serial message
    if (_currentData.length() > 0) {
        catchHandshake(_currentData);
        handleData(_currentData);

        _currentData = "";
    }
}

/**
 * Checks for a handshake message, when present it responds with a handshake message.
*/
void SerialController::catchHandshake(String data) {
    if (data == "X0") {
        Serial.println("X0"); 
        _handshakeConfirmed = true;
    }
}

/**
 * Handles all different event listeners and given data string.
*/
void SerialController::handleData(String data) {
    char type = data[0];

    if(_onData) {
        _onData(data);
    }

    switch (type)
    {
        case 'r':
            if (_onInitData) {
                _onInitData(data);
                Serial.println("cr");
            }
            break;
        case 'i':
            if (_onInstructionData) {
                _onInstructionData(data);
                Serial.println("ci");
            }
            break;
        case 's':
            if (_onSetterData) {
                _onSetterData(data);
                Serial.println("cs");
            }
            break;
        case 'g':
            if (_onGetterData) {
                _onGetterData(data);
                Serial.println("cg");
            }
            break;
        case 'f':
            if (_onFlushData) {
                _onFlushData(data);
                Serial.println("cf");
            }
            break;
    }
}

/**
 * Sets a eventlistener of given type to given callback function. Only allows one listener per event type.
*/
void SerialController::setEventListener(SerialEvent eventType, serialCallbackFunction func) {
    switch (eventType) {
        case Data: _onData = func;
        case Handshake: _onHandshake = func;
        case Init: _onInitData = func;
        case Instruction: _onInstructionData = func;
        case Setter: _onSetterData = func;
        case Getter: _onGetterData = func;
        case Flush: _onFlushData = func;
    }
}