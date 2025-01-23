#pragma once
#include <ArduinoJson.h>
#include "../Domain/Entities/Proprietor.hpp"

class JsonParser
{
public:
  static Proprietor parseProprietorConfiguration(const String &jsonString);
  static String createNotificationJson(int machineId, const String &state, double price);
};