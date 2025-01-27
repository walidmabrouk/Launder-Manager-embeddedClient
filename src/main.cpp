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
  }

  delay(BSP::System::TASK_INTERVAL_MS);
}