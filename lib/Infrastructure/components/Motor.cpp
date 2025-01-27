#include "Motor.h"

Motor::Motor(uint8_t relayPin) : _relayPin(relayPin),
                                 _isRunning(false),
                                 _startTime(0)
{
}

void Motor::init()
{
  pinMode(_relayPin, OUTPUT);
  stop();
}

void Motor::start()
{
  digitalWrite(_relayPin, BSP::Machine::IO::Motor::RELAY_ACTIVE_STATE);
  _isRunning = true;
  _startTime = millis();
}

void Motor::stop()
{
  digitalWrite(_relayPin, !BSP::Machine::IO::Motor::RELAY_ACTIVE_STATE);
  _isRunning = false;
  _startTime = 0;
}

void Motor::toggle()
{
  if (_isRunning)
  {
    stop();
  }
  else
  {
    start();
  }
}

bool Motor::isRunning() const
{
  return _isRunning;
}

void Motor::checkSafetyTimeout()
{
  if (_isRunning && (millis() - _startTime) > BSP::Machine::IO::Motor::MOTOR_SAFETY_TIMEOUT_MS)
  {
    stop();
  }
}