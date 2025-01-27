#include "../lib/Infrastructure/components/Button.h"
#include "../lib/Infrastructure/drivers/ButtonDriver.h"
#include "../lib/Infrastructure/components/Motor.h"
#include "../lib/Infrastructure/controllers/MotorController.h"



Button button;
ButtonDriver buttonDriver(button);
Motor motor;
MotorController motorController(motor, buttonDriver);

void setup()
{
  Serial.begin(BSP::Debug::SERIAL_BAUD_RATE);
  while (!Serial)
  {
    ; // Attendre la connexion série
  }

  button.init();
  motor.init();

  Serial.println(F("System initialized"));
}

void loop()
{
  motorController.update();

  static bool lastMotorState = false;
  if (motor.isRunning() != lastMotorState)
  {
    lastMotorState = motor.isRunning();
    Serial.println(lastMotorState ? F("Motor ON") : F("Motor OFF"));

    if (!lastMotorState)
    {
      // Afficher le temps de fonctionnement lorsque le moteur s'arrête
      unsigned long elapsedTime = motorController.getElapsedTime();
      Serial.print(F("Motor ran for: "));
      Serial.print(elapsedTime);
      Serial.println(F(" seconds"));
    }
  }

  if (motor.isRunning())
  {
    // Afficher le timer restant lorsque le moteur fonctionne
    Serial.print(F("Timer remaining: "));
    Serial.print(motorController.getTimer());
    Serial.println(F(" seconds"));

    if (motorController.getTimer() == 0)
    {
      Serial.println(F("Timer finished! Stopping motor."));
      motor.stop();
    }
  }

  delay(BSP::System::TASK_INTERVAL_MS);
}
