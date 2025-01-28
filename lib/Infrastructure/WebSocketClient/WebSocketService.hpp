#pragma once
#include <WebSocketsClient.h>
#include "../utils/JsonParser.hpp"

class WebSocketService
{
public:
  void begin(const char *host, uint16_t port, const char *path);
  void loop();
  void sendNotification(int machineId, const String &state, double price);

private:
  WebSocketsClient _webSocket;
  void webSocketEvent(WStype_t type, uint8_t *payload, size_t length);
};