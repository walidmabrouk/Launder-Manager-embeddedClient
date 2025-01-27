#ifndef BUTTON_DRIVER_H
#define BUTTON_DRIVER_H

#include "../components/Button.h"

class ButtonDriver
{
private:
    Button &_button;
    bool _lastState;

public:
    explicit ButtonDriver(Button &button);
    bool isPressed();
    bool isFallingEdge();
    bool isRisingEdge();
};

#endif // BUTTON_DRIVER_H