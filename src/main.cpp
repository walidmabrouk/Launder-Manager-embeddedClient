#include <Arduino.h>
#include "../lib/Infrastructure/WebSocketClient/WebSocketService.hpp"

const char *WIFI_SSID = "SABRINEBNAYED 6060";
const char *WIFI_PASSWORD = "sabrinesabrine";
const char *WS_HOST = "192.168.137.103";
const int WS_PORT = 5049;   
const char *WS_PATH = "/ws"; 

WebSocketService webSocketService;

void setup()
{
    Serial.begin(115200);

    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }

    Serial.println("\nConnecté au WiFi");
    Serial.print("Adresse IP: ");
    Serial.println(WiFi.localIP());

    webSocketService.begin(WS_HOST, WS_PORT, WS_PATH);
}

void loop()
{
    webSocketService.loop();

    static unsigned long lastSend = 0;
    if (millis() - lastSend > 5000)
    {
        lastSend = millis();
        webSocketService.sendNotification(30, "Stopped", 5.0);
    }
}