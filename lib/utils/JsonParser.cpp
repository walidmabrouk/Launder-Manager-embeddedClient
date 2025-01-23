#include "JsonParser.hpp"

Proprietor JsonParser::parseProprietorConfiguration(const String &jsonString)
{
  JsonDocument doc;
  DeserializationError error = deserializeJson(doc, jsonString);

  Proprietor proprietor;
  if (!error)
  {
    proprietor.Id = doc["Id"].as<int>();
    proprietor.Name = doc["Name"].as<std::string>();
    proprietor.Email = doc["Email"].as<std::string>();
    proprietor.TotalEarnings = doc["TotalEarnings"].as<double>();

    // Parse Laundries
    for (JsonObject laundryObj : doc["Laundries"].as<JsonArray>())
    {
      Laundry laundry;
      laundry.Id = laundryObj["Id"].as<int>();
      laundry.ProprietorId = laundryObj["ProprietorId"].as<int>();
      laundry.Name = laundryObj["Name"].as<std::string>();
      laundry.Address = laundryObj["Address"].as<std::string>();
      laundry.Earnings = laundryObj["Earnings"].as<double>();

      // Parse Machines
      for (JsonObject machineObj : laundryObj["Machines"].as<JsonArray>())
      {
        Machine machine;
        machine.Id = machineObj["Id"].as<int>();
        machine.LaundryId = machineObj["LaundryId"].as<int>();
        machine.SerialNumber = machineObj["SerialNumber"].as<std::string>();
        machine.Type = machineObj["Type"].as<std::string>();
        machine.State = machineObj["State"].as<std::string>();
        machine.Earnings = machineObj["Earnings"].as<double>();

        // Parse Cycles
        for (JsonObject cycleObj : machineObj["Cycles"].as<JsonArray>())
        {
          Cycle cycle;
          cycle.Id = cycleObj["Id"].as<int>();
          cycle.MachineId = cycleObj["MachineId"].as<int>();
          cycle.Name = cycleObj["Name"].as<std::string>();
          cycle.Price = cycleObj["Price"].as<double>();
          cycle.Duration = cycleObj["Duration"].as<std::string>();

          machine.Cycles.push_back(cycle);
        }

        laundry.Machines.push_back(machine);
      }

      proprietor.Laundries.push_back(laundry);
    }
  }

  return proprietor;
}

String JsonParser::createNotificationJson(int machineId, const String &state, double price)
{
  JsonDocument doc;
  doc["Type"] = "Notification";
  doc["machineId"] = machineId;
  doc["state"] = state;
  doc["price"] = price;

  String jsonString;
  serializeJson(doc, jsonString);
  return jsonString;
}