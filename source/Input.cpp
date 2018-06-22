#include "Input.hpp"

int Input::Scan()
{
    hidScanInput();
    touchCount = hidTouchCount();

    for (int i = 0; i < touchCount; i++)
        hidTouchRead(&touchPoints[i], i);

    return touchCount;
}

touchPosition* Input::GetPointPosition(int i)
{
    if (i < touchCount)
        return &touchPoints[i];
    else
        return NULL;
}