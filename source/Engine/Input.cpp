#include "Input.hpp"
#define ABS(x) ((x)<0?-(x):(x))

int Input::Scan()
{
    hidScanInput();

    _touchCount = hidTouchCount();
    _touchType = None;

    //If touch happens, check touch type
    if (_touchCount > 0)
    {
        //If touch is just pressed, get current app run time
        if (_touchPressTime == 0)
        {
            _touchPressTime = SDL_GetTicks();
            _touchPressed = true;
        }
        //If touch is held more then 500 ms, change event to pinch or drag
        if (SDL_GetTicks() - _touchPressTime >= 250)
        {
            _lastDragX = _touchPoints[0].px;
            _lastDragY = _touchPoints[0].py;
            _touchType = _touchCount > 1 ? Pinch : Drag;
        }
    }
    //Reset touch info
    else if (_touchPressTime > 0)
    {
        if (SDL_GetTicks() - _touchPressTime < 500)
            _touchType = Press;

        _touchPressTime = 0;
        _touchPressed = false;
        _firstPinch = true;
        _firstDrag = true;

        _lastDragX = 0;
        _lastDragY = 0;
        _lastPinchDelta = 0;

        _lastTouchInfo->ValueOne = 0;
        _lastTouchInfo->ValueTwo = 0;
    }

    //Store touch info
    for (int i = 0; i < _touchCount; i++)
        hidTouchRead(&_touchPoints[i], i);

    //Return is touch pressed
    return _touchCount;
}

TouchInfo* Input::GetTouchInfo()
{
    _lastTouchInfo->Type = None;
    if (_touchType == Press && !_touchPressed)
    {
        _lastTouchInfo->Type = Press;
        _lastTouchInfo->ValueOne = _touchPoints[0].px;
        _lastTouchInfo->ValueTwo = _touchPoints[0].py;
    } else if (_touchType == Drag)
    {
        _lastTouchInfo->Type = Drag;
        _lastTouchInfo->ValueOne = _touchPoints[0].px - _lastDragX;
        _lastTouchInfo->ValueTwo = _touchPoints[0].py - _lastDragY;
        
        if (_firstDrag)
        {
            _lastTouchInfo->ValueOne = 0;
            _lastTouchInfo->ValueTwo = 0;
            _firstDrag = false;
            _firstPinch = true;
        }
    } else if (_touchType == Pinch)
    {
        int x = _touchPoints[0].px - _touchPoints[1].px;
        int y = _touchPoints[0].py - _touchPoints[1].py;
        _lastTouchInfo->Type = Pinch;
        _lastTouchInfo->ValueOne = sqrt(fabs(x) + fabs(y));
        _lastTouchInfo->ValueTwo = 0;

        int lastPinch = _lastPinchDelta;
        _lastPinchDelta = _lastTouchInfo->ValueOne;
        _lastTouchInfo->ValueOne -= lastPinch;

        if (_firstPinch)
        {
            _lastTouchInfo->ValueOne = 0;
            _firstPinch = false;
            _firstDrag = true;
        }
    }
    return _lastTouchInfo;
}

touchPosition* Input::GetPointPosition(int i)
{
    if (i < _touchCount)
        return &_touchPoints[i];
    else
        return NULL;
}