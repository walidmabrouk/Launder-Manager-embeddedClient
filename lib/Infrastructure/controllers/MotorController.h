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

  unsigned long _startTime;   // Temps de démarrage du moteur
  unsigned long _elapsedTime; // Temps total de fonctionnement
  int _timer;                 // Timer pour 20 secondes

public:
  MotorController(Motor &motor, ButtonDriver &buttonDriver);

  void update();
  bool isMotorRunning() const;
  int getTimer() const;           // Récupérer le temps restant
  unsigned long getElapsedTime(); // Récupérer le temps écoulé
};

#endif // MOTORCONTROLLER_H