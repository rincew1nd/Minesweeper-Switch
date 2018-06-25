#include "Input.hpp"
#include <switch.h>
#include <cstdio>

int Input::Scan()
{
    hidScanInput();

    _touchCount = hidTouchCount();

    //Prevent multiple clicks from one touch press
    if (_touchCount == 0)
        _released = true;
    else 
        if (!_released)
            _touchCount = 0;
        else
            _released = false;

    for (int i = 0; i < _touchCount; i++)
        hidTouchRead(&_touchPoints[i], i);

    return _touchCount;
}

touchPosition* Input::GetPointPosition(int i)
{
    if (i < _touchCount)
        return &_touchPoints[i];
    else
        return NULL;
}