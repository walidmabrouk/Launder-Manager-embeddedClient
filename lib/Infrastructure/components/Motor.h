#ifndef MOTOR_H
#define MOTOR_H

#include <Arduino.h>
#include "../../include/BSP.hpp"

class Motor
{
private:
  const uint8_t _relayPin;
  bool _isRunning;
  unsigned long _startTime;

public:
  explicit Motor(uint8_t relayPin = BSP::Machine::IO::Motor::RELAY_PIN);
  ~Motor() = default;

  // Prévenir la copie
  Motor(const Motor &) = delete;
  Motor &operator=(const Motor &) = delete;

  void init();
  void start();
  void stop();
  void toggle();
  bool isRunning() const;

private:
  void checkSafetyTimeout();
};

#endif // MOTOR_H