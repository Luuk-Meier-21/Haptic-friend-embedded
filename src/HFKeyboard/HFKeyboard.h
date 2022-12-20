#ifndef HFKeyboard_h
#define HFKeyboard_h

#include <Arduino.h>
#include <Keyboard.h>
#include "/Users/luukmeier/Documents/Repos/Haptic Friend/arduino/src/HFButton/HFButton.h"

const int maxNodes = 20;

enum class ListenerType: char { 
    Empty = 'z',
    KeystrokeClick = 'a',
    KeystrokePress = 'b',
    KeystrokeRelease = 'c'
};

class Node {
    public: 
        Node(char id, int inputPin, int outputPin);
        Node();
        char id;
        int inputPin;
        int outputPin;
        bool valid;
        HFButton button = NULL;
    private:
        void attachInteraction(char keystroke);
};

class Listener {
    public: 
        Listener(Node node, ListenerType type, char keystroke);
        Listener();
        Node node;
        ListenerType type;
        char keystroke;
        bool valid;
    private:
        void attachInteraction();
};  

class HFKeyboard {
    public:
        HFKeyboard();
        void setup();
        void tick();
        
        // Node:
        Node addNode(char id, int inputPin, int outputPin);
        Node findNode(char id);
        void logNodes();

        // Listeners
        bool addListener(char node, char type, char keystroke);     
        void logListeners();
        int findListenerIndex(char nodeChar);
        Listener findListener(char nodeChar);
        void clearListener(int index);
        
    private:
        Node _nodes[maxNodes];
        int _nodesLength = 0;   
    
        Listener _listeners[maxNodes];
        int _listenersLength = 0;

        template <size_t n, class T> void push(T (&arr)[n], int &index, T const value);
        // template <size_t n, class T> T pop(T (&arr)[n]);
};
#endif