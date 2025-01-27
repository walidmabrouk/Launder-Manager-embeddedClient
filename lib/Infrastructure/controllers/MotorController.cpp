#include "MotorController.h"
#include <Arduino.h>

MotorController::MotorController(Motor &motor, ButtonDriver &buttonDriver)
    : _motor(motor), _buttonDriver(buttonDriver), _lastButtonState(false),
      _lastToggleTime(0), _startTime(0), _elapsedTime(0), _timer(20)
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
      if (_motor.isRunning())
      {
        _startTime = millis(); // Enregistrer le temps de démarrage
        _timer = 20;           // Réinitialiser le timer
      }
      else
      {
        // Calculer le temps écoulé
        _elapsedTime += (millis() - _startTime) / 1000;
      }
      _lastToggleTime = currentTime;
    }
  }

  // Mettre à jour le timer
  if (_motor.isRunning() && _timer > 0)
  {
    static unsigned long lastUpdateTime = millis();
    if (millis() - lastUpdateTime >= 1000)
    {
      _timer--;
      lastUpdateTime = millis();
    }
  }
}

bool MotorController::isMotorRunning() const
{
  return _motor.isRunning();
}

int MotorController::getTimer() const
{
  return _timer;
}

unsigned long MotorController::getElapsedTime()
{
  unsigned long totalElapsedTime = _elapsedTime;
  if (_motor.isRunning())
  {
    totalElapsedTime += (millis() - _startTime) / 1000;
  }
  return totalElapsedTime;
}
