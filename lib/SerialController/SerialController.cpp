#include "Arduino.h"
#include "SerialController.h"

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

void SerialController::catchHandshake(String data) {
    if (data == "X0") {
        Serial.println("X0"); 
        _handshakeConfirmed = true;
    }
}

void SerialController::handleData(String data) {
    char type = data[0];

    if(_onData)                             _onData(data);
    if(type == 'i' && _onInstructionData)   _onInstructionData(data);
    if(type == 's' && _onSetterData)        _onSetterData(data);
}

void SerialController::setEventListener(SerialEvent eventType, serialCallbackFunction func) {
    switch (eventType) {
        case Data: _onData = func;
        case Handshake: _onHandshake = func;
        case Instruction: _onInstructionData = func;
        case Setter: _onSetterData = func;
    }
}