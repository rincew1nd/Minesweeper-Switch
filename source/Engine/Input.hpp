#pragma once

#include <switch.h>
#include <SDL2/SDL.h>

enum InputType
{
    None,
    Press,
    Drag,
    Pinch
};

typedef struct TouchInfo
{
    InputType Type;
    int ValueOne;
    int ValueTwo;
} TouchInfo;

class Input
{
    public:
        int Scan();
        touchPosition* GetPointPosition(int);
        TouchInfo* GetTouchInfo();
        
    private:
        touchPosition _touchPoints[10];

        InputType _touchType = None;
        int _lastDragX = 0;
        int _lastDragY = 0;
        int _lastPinchDelta = 0;

        TouchInfo* _lastTouchInfo = new TouchInfo();
        
        int _touchCount = 0;
        bool _touchPressed = false;
        bool _firstPinch = true;
        bool _firstDrag = true;
        Uint32 _touchPressTime = 0;
};