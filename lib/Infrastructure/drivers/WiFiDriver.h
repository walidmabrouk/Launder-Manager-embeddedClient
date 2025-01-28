// DriverWiFi.h
#ifndef DRIVER_WIFI_H
#define DRIVER_WIFI_H

#include <Arduino.h>
#include <WiFi.h>
#include "../../include/BSP.hpp"

class WiFiDriver
{
private:
    WiFiClient &_wifiClient;
    Types::NetworkConfig _config;
    unsigned long _timeout;
    bool _isConnected;

public:
    explicit WiFiDriver(WiFiClient &wifiClient,
                        const Types::NetworkConfig &config = getDefaultNetworkConfig(),
                        unsigned long timeout = BSP::System::WATCHDOG_TIMEOUT_MS);
    ~WiFiDriver() = default;

    void init();
    bool connect();
    void disconnect();
    bool isConnected() const;
    IPAddress getLocalIP() const;
    int32_t getRSSI() const;

    // Accesseurs pour la configuration
    const Types::NetworkConfig &getConfig() const { return _config; }
    void setConfig(const Types::NetworkConfig &config) { _config = config; }
};

#endif // DRIVER_WIFI_H