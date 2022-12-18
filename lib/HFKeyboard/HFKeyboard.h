#ifndef HFKeyboard_h
#define HFKeyboard_h

#include <Arduino.h>
#include <HFButton.h>

# define my_sizeof(type) ((char *)(&type+1)-(char*)(&type))

const int maxNodes = 20;

struct InputNode {
    char id;
    int inputPin;
    int outputPin;
    bool valid;
};

struct Listener {
    InputNode node;
    String type;
    char keystroke;
    bool valid;
};

class HFKeyboard {
    public:
        HFKeyboard();
        void setup();
        void tick();
        
        // Node:
        InputNode createNode(char id, int inputPin, int outputPin);
        InputNode createNode(bool isValid);
        InputNode addNode(char id, int inputPin, int outputPin);
        InputNode findNode(char id);

        // Listeners
        Listener createListener(char node, char type, char keystroke);
        Listener createListener(bool isValid);
        void addListener(Listener listener);

        enum ListenerType: char { 
            empty = 'x', 
            keystroke = 'a' 
        };
        
    private:
        InputNode _nodes[maxNodes];
        int _nodesLength = 0;
        
        Listener _listeners[maxNodes];
        int _listenersLength = 0;

        template <size_t n, class T> void push(T (&arr)[n], int &index, T const value);
        template <size_t n, class T> T HFKeyboard::pop(T (&arr)[n]);
};
#endif