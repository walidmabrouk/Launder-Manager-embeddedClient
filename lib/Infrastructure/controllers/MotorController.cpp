#include "MotorController.h"

MotorController::MotorController(Motor &motor, ButtonDriver &buttonDriver) : _motor(motor),
                                                                             _buttonDriver(buttonDriver),
                                                                             _lastButtonState(false),
                                                                             _lastToggleTime(0)
{
}

void MotorController::update()
{
  if (_buttonDriver.isRisingEdge())
  {
    unsigned long currentTime = millis();
    if (currentTime - _lastToggleTime >= DEBOUNCE_DELAY)
    {
      _motor.toggle();
      _lastToggleTime = currentTime;
    }
  }
}

bool MotorController::isMotorRunning() const
{
  return _motor.isRunning();
}