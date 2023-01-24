#ifndef HFKeyboard_h
#define HFKeyboard_h

#include <Arduino.h>
#include <Keyboard.h>
#include "/Users/luukmeier/Documents/Repos/Haptic Friend/arduino/src/HFButton/HFButton.h"

const int maxNodes = 20;

struct ListenerOptions {
    bool leftShift = false;     // a
    bool rightShift = false;    // b
    bool leftCtrl = false;      // c
    bool rightCtrl = false;     // d
};

template<class PT, class OT>
class Node {
    public: 
    
        Node(char id, int inputPin, int outputPin);
        Node();
        char id;
        int inputPin;
        int outputPin;
        bool valid;
        HFButton<PT, OT> button = NULL;
    private:
        void attachInteraction(char keystroke);
};

typedef HFButton<char, ListenerOptions> ListenerHFButton;
typedef Node<char, ListenerOptions> ListenerNode;

enum class ListenerType: char { 
    Empty = 'x',
    Keystroke = 'a',
    Arrows = 'b'
};

class Listener {
    public: 
        Listener(ListenerNode node, ListenerType type, char keystroke, ListenerOptions options);
        Listener();
        ListenerNode node;
        ListenerType type;
        char keystroke;
        ListenerOptions options;
        bool valid;
    private:
        void pressKeystroke(char keystroke);
        void releaseKeystroke(char keystroke);
        void attachInteraction();
};  

class HFKeyboard {
    public:
        HFKeyboard();
        void setup();
        void tick();
        
        // Node:
        ListenerNode defineNode(char id, int inputPin, int outputPin);
        ListenerNode findNode(char id);
        void logNodes();

        // Listeners
        bool addListener(char node, char type, char keystroke, String options);   
        ListenerOptions getListenerOptions(String optionsString);
        void logListeners();
        int findListenerIndex(char nodeChar);
        Listener findListener(char nodeChar);
        void clearListener(int index);
        void clearListeners();
        
    private:
        ListenerNode _nodes[maxNodes];
        int _nodesLength = 0;   
    
        Listener _listeners[maxNodes];
        int _listenersLength = 0;

        template <size_t n, class T> void push(T (&arr)[n], int &index, T const value);
        // template <size_t n, class T> T pop(T (&arr)[n]);
};
#endif