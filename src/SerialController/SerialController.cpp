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


void SerialController::callEvent(serialCallbackFunction func, String data, char type) {
    if (func) {
        bool succes = func(data);
        String state = succes ? "c" : "r";
        String message = state + data;
        Serial.println(message);
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
        case 'i': callEvent(_onInstructionData, data, 'i'); break;
        case 's': callEvent(_onSetterData, data, 's'); break;
        case 'g': callEvent(_onGetterData, data, 'g'); break;
        case 'f': callEvent(_onFlushData, data, 'f'); break;
    }
}

/**
 * Sets a eventlistener of given type to given callback function. Only allows one listener per event type.
*/
void SerialController::setEventListener(SerialEvent eventType, serialCallbackFunction func) {
    switch (eventType) {
        case Data: _onData = func;
        case Handshake: _onHandshake = func;
        case Instruction: _onInstructionData = func;
        case Setter: _onSetterData = func;
        case Getter: _onGetterData = func;
        case Flush: _onFlushData = func;
    }
}