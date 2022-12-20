#ifndef SerialController_h
#define SerialController_h

#include <Arduino.h>

extern "C" {
    typedef void (*serialCallbackFunction)(String);
    typedef void (*serialCallbackFunctionArray)(String);
}

class SerialController {
    public:

        void use(serialCallbackFunction serialDataFunc);
        void tick();

        enum SerialEvent { Data, Handshake, Instruction, Setter, Getter, Flush };
        void setEventListener(SerialEvent eventType, serialCallbackFunction func);

    private:
        void catchHandshake(String message);
        void handleData(String data);

        String _currentData = "";
        bool _handshakeConfirmed = false;

        serialCallbackFunction _onData = NULL;
        serialCallbackFunction _onHandshake = NULL;
        serialCallbackFunction _onInstructionData = NULL;
        serialCallbackFunction _onSetterData = NULL;
        serialCallbackFunction _onGetterData = NULL;
        serialCallbackFunction _onFlushData = NULL;
};  
#endif
