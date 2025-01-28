// DriverWiFi.cpp
#include "WiFiDriver.h"

WiFiDriver::WiFiDriver(WiFiClient &wifiClient,
                       const Types::NetworkConfig &config,
                       unsigned long timeout)
    : _wifiClient(wifiClient), _config(config), _timeout(timeout), _isConnected(false)
{
  if (BSP::Debug::ENABLE_SERIAL)
  {
    Serial.begin(BSP::Debug::SERIAL_BAUD_RATE);
  }
}

void WiFiDriver::init()
{
  WiFi.mode(WIFI_STA);
  disconnect();

  if (BSP::Debug::ENABLE_SERIAL)
  {
    Serial.println("WiFi initialisé en mode Station");
  }
}

bool WiFiDriver::connect()
{
  if (BSP::Debug::ENABLE_SERIAL)
  {
    Serial.println("Connexion au Wi-Fi...");
    Serial.print("SSID: ");
    Serial.println(_config.wifi_ssid);
  }

  WiFi.begin(_config.wifi_ssid, _config.wifi_password);

  unsigned long startAttemptTime = millis();

  while (WiFi.status() != WL_CONNECTED &&
         millis() - startAttemptTime < _timeout)
  {
    delay(BSP::System::TASK_INTERVAL_MS * 50); // 500ms
    if (BSP::Debug::ENABLE_SERIAL)
    {
      Serial.print(".");
    }
  }

  _isConnected = (WiFi.status() == WL_CONNECTED);

  if (BSP::Debug::ENABLE_SERIAL)
  {
    if (_isConnected)
    {
      Serial.println("\nConnecté au Wi-Fi!");
      Serial.print("Adresse IP: ");
      Serial.println(WiFi.localIP());
    }
    else
    {
      Serial.println("\nÉchec de la connexion Wi-Fi!");
    }
  }

  return _isConnected;
}

void WiFiDriver::disconnect()
{
  WiFi.disconnect();
  _isConnected = false;

  if (BSP::Debug::ENABLE_SERIAL)
  {
    Serial.println("Déconnecté du Wi-Fi");
  }
}

bool WiFiDriver::isConnected() const
{
  return WiFi.status() == WL_CONNECTED;
}

IPAddress WiFiDriver::getLocalIP() const
{
  return WiFi.localIP();
}

int32_t WiFiDriver::getRSSI() const
{
  return WiFi.RSSI();
}
