#ifndef MOTOR_CONTROLLER_H
#define MOTOR_CONTROLLER_H

#include "../components/Motor.h"
#include "../drivers/ButtonDriver.h"

class MotorController
{
private:
  Motor &_motor;
  ButtonDriver &_buttonDriver;
  bool _lastButtonState;
  unsigned long _lastToggleTime;
  static constexpr unsigned long DEBOUNCE_DELAY = 50;

public:
  MotorController(Motor &motor, ButtonDriver &buttonDriver);

  // Prévenir la copie
  MotorController(const MotorController &) = delete;
  MotorController &operator=(const MotorController &) = delete;

  void update();
  bool isMotorRunning() const;
};

#endif // MOTOR_CONTROLLER_H