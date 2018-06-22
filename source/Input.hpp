#include <switch.h>

class Input
{
    public:
        int Scan();
        touchPosition* GetPointPosition(int);
    private:
        touchPosition touchPoints[10];
        int touchCount;
};