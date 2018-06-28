#pragma once

#include <functional>
#include "GraphicalObject.hpp"

class TouchableObject : public virtual GraphicalObject
{
    public:
        TouchableObject(int, int, int, int);
        void SetAction(std::function<void()>);
        void Press() { _onPress(); };
        bool Hovered(touchPosition*);
    
    private:
        std::function<void()> _onPress;
};