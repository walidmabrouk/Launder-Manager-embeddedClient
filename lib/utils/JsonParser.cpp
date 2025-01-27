#include "JsonParser.hpp"
#include <ArduinoJson.h>

Proprietor JsonParser::parseProprietorConfiguration(const String &jsonString)
{
  StaticJsonDocument<2048> doc;
  DeserializationError error = deserializeJson(doc, jsonString);

  Proprietor proprietor;
  if (error)
  {
    Serial.printf("JSON Parsing Error: %s\n", error.c_str());
    return proprietor;
  }

  proprietor.Id = doc["Id"].as<int>();
  proprietor.Name = doc["Name"].as<std::string>();
  proprietor.Email = doc["Email"].as<std::string>();
  proprietor.TotalEarnings = doc["TotalEarnings"].as<double>();

  for (JsonObject laundryObj : doc["Laundries"].as<JsonArray>())
  {
    Laundry laundry = parseLaundry(laundryObj);
    proprietor.Laundries.push_back(laundry);
  }

  return proprietor;
}

Laundry JsonParser::parseLaundry(JsonObject laundryObj)
{
  Laundry laundry;
  laundry.Id = laundryObj["Id"].as<int>();
  laundry.ProprietorId = laundryObj["ProprietorId"].as<int>();
  laundry.Name = laundryObj["Name"].as<std::string>();
  laundry.Address = laundryObj["Address"].as<std::string>();
  laundry.Earnings = laundryObj["Earnings"].as<double>();

  for (JsonObject machineObj : laundryObj["Machines"].as<JsonArray>())
  {
    Machine machine = parseMachine(machineObj);
    laundry.Machines.push_back(machine);
  }

  return laundry;
}

Machine JsonParser::parseMachine(JsonObject machineObj)
{
  Machine machine;
  machine.Id = machineObj["Id"].as<int>();
  machine.LaundryId = machineObj["LaundryId"].as<int>();
  machine.SerialNumber = machineObj["SerialNumber"].as<std::string>();
  machine.Type = machineObj["Type"].as<std::string>();
  machine.State = machineObj["State"].as<std::string>();
  machine.Earnings = machineObj["Earnings"].as<double>();

  for (JsonObject cycleObj : machineObj["Cycles"].as<JsonArray>())
  {
    Cycle cycle = parseCycle(cycleObj);
    machine.Cycles.push_back(cycle);
  }

  return machine;
}

Cycle JsonParser::parseCycle(JsonObject cycleObj)
{
  Cycle cycle;
  cycle.Id = cycleObj["Id"].as<int>();
  cycle.MachineId = cycleObj["MachineId"].as<int>();
  cycle.Name = cycleObj["Name"].as<std::string>();
  cycle.Price = cycleObj["Price"].as<double>();
  cycle.Duration = cycleObj["Duration"].as<std::string>();
  return cycle;
}

String JsonParser::createNotificationJson(int machineId, const String &state, double price)
{
  StaticJsonDocument<512> doc;
  doc["Type"] = "Notification";
  doc["machineId"] = machineId;
  doc["state"] = state;
  doc["price"] = price;

  String jsonString;
  serializeJson(doc, jsonString);
  return jsonString;
}