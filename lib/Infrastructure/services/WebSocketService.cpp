#include "WebSocketService.h"
#include <Arduino.h> // Ensure Arduino framework is included

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
  if (!_webSocket.isConnected())
  {
    Serial.println("[WSc] WebSocket not connected. Cannot send notification.");
    return;
  }

  String notification = JsonParser::createNotificationJson(machineId, state, price);
  _webSocket.sendTXT(notification);
}

void WebSocketService::webSocketEvent(WStype_t type, uint8_t *payload, size_t length)
{
  switch (type)
  {
  case WStype_CONNECTED:
    Serial.println("[WSc] Connected to server");
    break;

  case WStype_TEXT:
  {
    String message = String((char *)payload);
    if (message.indexOf("\"Type\":\"Configuration\"") != -1)
    {
      Proprietor proprietor = JsonParser::parseProprietorConfiguration(message);
      // Handle the configuration here
      Serial.printf("Configuration received for: %s\n", proprietor.Name.c_str());
    }
    break;
  }

  case WStype_DISCONNECTED:
    Serial.println("[WSc] Disconnected from server");
    break;

  default:
    Serial.printf("[WSc] Event type %d not handled\n", type);
    break;
  }
}
