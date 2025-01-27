#ifndef BUTTON_H
#define BUTTON_H

#include <Arduino.h>
#include "../../include/BSP.hpp"

class Button
{
private:
    const uint8_t _pin;
    bool _currentState;
    bool _previousState;
    unsigned long _lastDebounceTime;

public:
    explicit Button(uint8_t pin = BSP::Machine::IO::Buttons::DEFAULT_BUTTON_PIN) : _pin(pin),
                                                                                   _currentState(false),
                                                                                   _previousState(false),
                                                                                   _lastDebounceTime(0)
    {
    }

    ~Button() = default;
    Button(const Button &) = delete;
    Button &operator=(const Button &) = delete;

    void init();
    bool isPressed();
    bool getPreviousState() const;
    uint8_t getPin() const;
};

#endif // BUTTON_H