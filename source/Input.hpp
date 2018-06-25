#include <switch.h>

class Input
{
    public:
        int Scan();
        touchPosition* GetPointPosition(int);
    private:
        touchPosition _touchPoints[10];
        int _touchCount;
        bool _released;
};