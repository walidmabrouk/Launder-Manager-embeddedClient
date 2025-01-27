#include "../lib/Infrastructure/components/Button.h"
#include "../lib/Infrastructure/drivers/ButtonDriver.h"
#include "../lib/Infrastructure/components/Motor.h"
#include "../lib/Infrastructure/controllers/MotorController.h"
#include "../lib/Infrastructure/components/Display.h"

// Déclaration des objets
Button button;
ButtonDriver buttonDriver(button);
Motor motor;
MotorController motorController(motor, buttonDriver);
Display display;

void setup()
{
  Serial.begin(BSP::Debug::SERIAL_BAUD_RATE);
  while (!Serial)
  {
    ; // Attendre la connexion série
  }

  Wire.begin(); // Initialisation I2C pour ESP32 (SDA=21, SCL=22 par défaut)

  button.init();
  motor.init();
  display.init();

  Serial.println(F("System initialized"));
}

void loop()
{
  motorController.update();

  // Mise à jour de l'affichage
  display.updateStatus(
      motor.isRunning(),
      motorController.getTimer(),
      motorController.getElapsedTime());

  // Gestion des changements d'état du moteur
  static bool lastMotorState = false;
  if (motor.isRunning() != lastMotorState)
  {
    lastMotorState = motor.isRunning();
    Serial.println(lastMotorState ? F("Motor ON") : F("Motor OFF"));

    if (!lastMotorState)
    {
      unsigned long elapsedTime = motorController.getElapsedTime();
      Serial.print(F("Motor ran for: "));
      Serial.print(elapsedTime);
      Serial.println(F(" seconds"));
    }
  }

  // Affichage du timer et arrêt du moteur si nécessaire
  if (motor.isRunning())
  {
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