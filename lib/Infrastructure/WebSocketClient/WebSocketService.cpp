#include "WebSocketService.hpp"

void WebSocketService::begin(const char *host, uint16_t port, const char *path)
{
  _webSocket.begin(host, port, path);
  _webSocket.onEvent([this](WStype_t type, uint8_t *payload, size_t length)
                     { this->webSocketEvent(type, payload, length); });
}

void WebSocketService::loop()
{
  _webSocket.loop();
}

void WebSocketService::sendNotification(int machineId, const String &state, double price)
{
  String notification = JsonParser::createNotificationJson(machineId, state, price);
  _webSocket.sendTXT(notification);
}

void WebSocketService::webSocketEvent(WStype_t type, uint8_t *payload, size_t length)
{
  switch (type)
  {
  case WStype_CONNECTED:
    Serial.println("[WSc] Connecté au serveur");
    break;

  case WStype_TEXT:
  {
    String message = String((char *)payload);
    if (message.indexOf("\"Type\":\"Configuration\"") != -1)
    {
      Proprietor proprietor = JsonParser::parseProprietorConfiguration(message);
      // Traitez la configuration ici
      Serial.printf("Configuration reçue pour: %s\n", proprietor.Name.c_str());
    }
    break;
  }
  }
}