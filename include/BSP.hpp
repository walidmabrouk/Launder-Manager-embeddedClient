// ConfigBSP.hpp
#pragma once

#include <cstdint>

namespace BSP
{
  namespace Network
  {
    namespace WiFi
    {
      constexpr char SSID[] = "SABRINEBNAYED 6060";
      constexpr char PASSWORD[] = "sabrinesabrine";
    }

    namespace WebSocket
    {
      constexpr char HOST[] = "192.168.137.103";
      constexpr uint16_t PORT = 5049;
      constexpr char PATH[] = "/ws";
    }
  }

  namespace Machine
  {
    constexpr uint8_t DEFAULT_ID = 2;

    namespace IO
    {
      namespace Buttons
      {
        // Constantes génériques pour tous les boutons
        constexpr unsigned long DEBOUNCE_DELAY_MS = 50;
        constexpr bool ACTIVE_STATE = LOW;        // Pour INPUT_PULLUP
        constexpr uint8_t DEFAULT_BUTTON_PIN = 23; // Ajout de cette ligne

        // Pins spécifiques
        namespace Control
        {
          constexpr uint8_t START_PIN = 12;
          constexpr uint8_t STOP_PIN = 13;
        }
      }
      namespace Motor
      {
        constexpr uint8_t RELAY_PIN = 22;
        constexpr bool RELAY_ACTIVE_STATE = HIGH;
        constexpr unsigned long MOTOR_SAFETY_TIMEOUT_MS = 3600000; // 1 heure
      }
    }
  }

  // Configuration de débogage
  namespace Debug
  {
    constexpr bool ENABLE_SERIAL = true;
    constexpr unsigned long SERIAL_BAUD_RATE = 115200;
  }

  // Configurations du système
  namespace System
  {
    constexpr unsigned long WATCHDOG_TIMEOUT_MS = 5000;
    constexpr unsigned long TASK_INTERVAL_MS = 10;
  }
}

// Types personnalisés pour améliorer la lisibilité et la maintenance
namespace Types
{
  struct NetworkConfig
  {

    const char *wifi_ssid;
    const char *wifi_password;
    const char *ws_host;
    uint16_t ws_port;
    const char *ws_path;
  };

  struct ButtonConfig
  {
    uint8_t pin;
    unsigned long debounce_delay;
    bool active_state;
  };

  struct MachineConfig
  {
    uint8_t id;
    ButtonConfig start_button;
    ButtonConfig stop_button;
  };
}

// Fonction helper pour obtenir la configuration par défaut
inline Types::NetworkConfig getDefaultNetworkConfig()
{
  return {
      BSP::Network::WiFi::SSID,
      BSP::Network::WiFi::PASSWORD,
      BSP::Network::WebSocket::HOST,
      BSP::Network::WebSocket::PORT,
      BSP::Network::WebSocket::PATH};
}

inline Types::MachineConfig getDefaultMachineConfig()
{
  return {
      BSP::Machine::DEFAULT_ID,
      {BSP::Machine::IO::Buttons::Control::START_PIN,
       BSP::Machine::IO::Buttons::DEBOUNCE_DELAY_MS,
       BSP::Machine::IO::Buttons::ACTIVE_STATE},
      {BSP::Machine::IO::Buttons::Control::STOP_PIN,
       BSP::Machine::IO::Buttons::DEBOUNCE_DELAY_MS,
       BSP::Machine::IO::Buttons::ACTIVE_STATE}};
}