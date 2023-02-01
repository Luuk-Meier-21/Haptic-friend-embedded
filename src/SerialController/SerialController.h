#ifndef SerialController_h
#define SerialController_h

#include <Arduino.h>

class SerialController {
    public:
        typedef bool (*serialCallbackFunction)(String);
        typedef void (*serialCallbackFunctionArray)(String);

        void use(serialCallbackFunction serialDataFunc);
        void tick();

        enum SerialEvent { Data, Handshake, Instruction, Setter, Getter, Flush };
        void setEventListener(SerialEvent eventType, serialCallbackFunction func);

    private:
        void catchHandshake(String message);
        void handleData(String data);
        void callEvent(serialCallbackFunction func, String data, char type);

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
