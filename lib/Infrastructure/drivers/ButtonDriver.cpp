#include "ButtonDriver.h"

ButtonDriver::ButtonDriver(Button &button) : _button(button),
                                             _lastState(false)
{
}

bool ButtonDriver::isPressed()
{
  return _button.isPressed();
}

bool ButtonDriver::isFallingEdge()
{
  bool currentState = _button.isPressed();
  bool fallingEdge = (_lastState && !currentState);
  _lastState = currentState;
  return fallingEdge;
}

bool ButtonDriver::isRisingEdge()
{
  bool currentState = _button.isPressed();
  bool risingEdge = (!_lastState && currentState);
  _lastState = currentState;
  return risingEdge;
}