#include "../lib/Infrastructure/components/Button.h"
#include "../lib/Infrastructure/drivers/ButtonDriver.h"
#include "../lib/Infrastructure/components/Motor.h"
#include "../lib/Infrastructure/controllers/MotorController.h"
#include "../lib/Infrastructure/components/Display.h"
#include "../lib/Infrastructure/drivers/WiFiDriver.h"
#include "../lib/Infrastructure/services/WebSocketService.h"

// Déclaration des objets
Button button;
ButtonDriver buttonDriver(button);
Motor motor;
MotorController motorController(motor, buttonDriver);
Display display;
WiFiClient wifiClient;
WiFiDriver wifiDriver(wifiClient);
WebSocketService webSocketService;

// État précédent du moteur pour détecter les changements
static bool lastMotorState = false;

void setupWiFi()
{
  wifiDriver.init();
  if (wifiDriver.connect())
  {
    Serial.println(F("WiFi connected successfully"));
    Serial.print(F("IP address: "));
    Serial.println(wifiDriver.getLocalIP());
    Serial.print(F("Signal strength (RSSI): "));
    Serial.println(wifiDriver.getRSSI());

    // Initialiser WebSocket une fois le WiFi connecté
    webSocketService.begin(
        BSP::Network::WebSocket::HOST,
        BSP::Network::WebSocket::PORT,
        BSP::Network::WebSocket::PATH);
  }
  else
  {
    Serial.println(F("WiFi connection failed"));
  }
}

void checkWiFiStatus()
{
  static unsigned long lastWiFiCheck = 0;
  static bool lastWiFiStatus = false;

  unsigned long currentMillis = millis();
  if (currentMillis - lastWiFiCheck >= 5000)
  {
    lastWiFiCheck = currentMillis;

    bool currentWiFiStatus = wifiDriver.isConnected();
    if (currentWiFiStatus != lastWiFiStatus)
    {
      lastWiFiStatus = currentWiFiStatus;
      if (currentWiFiStatus)
      {
        Serial.println(F("WiFi reconnected"));
        Serial.print(F("IP: "));
        Serial.println(wifiDriver.getLocalIP());

        // Réinitialiser WebSocket après reconnexion WiFi
        webSocketService.begin(
            BSP::Network::WebSocket::HOST,
            BSP::Network::WebSocket::PORT,
            BSP::Network::WebSocket::PATH);
      }
      else
      {
        Serial.println(F("WiFi connection lost"));
        wifiDriver.connect();
      }
    }
  }
}

void handleMotorStateChange()
{
  bool currentMotorState = motor.isRunning();
  if (currentMotorState != lastMotorState)
  {
    lastMotorState = currentMotorState;
    Serial.println(currentMotorState ? F("Motor ON") : F("Motor OFF"));

    // Envoyer notification WebSocket du changement d'état
    webSocketService.sendNotification(
        BSP::Machine::DEFAULT_ID,
        currentMotorState ? "ON" : "OFF",
        0.0 // Prix à ajuster selon vos besoins
    );

    if (!currentMotorState)
    {
      unsigned long elapsedTime = motorController.getElapsedTime();
      Serial.print(F("Motor ran for: "));
      Serial.print(elapsedTime);
      Serial.println(F(" seconds"));
    }
  }
}

void setup()
{
  Serial.begin(BSP::Debug::SERIAL_BAUD_RATE);
  while (!Serial)
  {
    ; // Attendre la connexion série
  }

  Wire.begin(); // Initialisation I2C pour ESP32

  button.init();
  motor.init();
  display.init();

  // Configuration et connexion WiFi + WebSocket
  setupWiFi();

  Serial.println(F("System initialized"));
}

void loop()
{
  // Vérification périodique du WiFi
  checkWiFiStatus();

  // Mise à jour WebSocket
  webSocketService.loop();

  // Mise à jour du contrôleur moteur
  motorController.update();

  // Mise à jour de l'affichage
  display.updateStatus(
      motor.isRunning(),
      motorController.getTimer(),
      motorController.getElapsedTime());

  // Gestion des changements d'état du moteur et notifications WebSocket
  handleMotorStateChange();

  // Gestion du timer et arrêt du moteur si nécessaire
  if (motor.isRunning())
  {
    Serial.print(F("Timer remaining: "));
    Serial.print(motorController.getTimer());
    Serial.println(F(" seconds"));

    if (motorController.getTimer() == 0)
    {
      Serial.println(F("Timer finished! Stopping motor."));
      motor.stop();
      // Notification WebSocket de l'arrêt automatique
      webSocketService.sendNotification(
          BSP::Machine::DEFAULT_ID,
          "Stopped",
          5.0 // Prix à ajuster selon vos besoins
      );
    }
  }

  delay(BSP::System::TASK_INTERVAL_MS);
}