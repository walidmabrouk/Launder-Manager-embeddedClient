#include "Button.h"

void Button::init()
{
  pinMode(_pin, INPUT_PULLUP);
  _currentState = digitalRead(_pin);
  _previousState = _currentState;
}

bool Button::isPressed()
{
  bool reading = digitalRead(_pin);

  if (reading != _previousState)
  {
    _lastDebounceTime = millis();
  }

  if ((millis() - _lastDebounceTime) > BSP::Machine::IO::Buttons::DEBOUNCE_DELAY_MS)
  {
    if (reading != _currentState)
    {
      _currentState = reading;
    }
  }

  _previousState = reading;
  return _currentState == BSP::Machine::IO::Buttons::ACTIVE_STATE;
}

bool Button::getPreviousState() const
{
  return _previousState;
}

uint8_t Button::getPin() const
{
  return _pin;
}