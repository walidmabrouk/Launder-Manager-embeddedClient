#pragma once
#include <vector>
#include <string>
#include "Cycle.hpp"

struct Machine
{
    int Id;
    int LaundryId;
    std::string SerialNumber;
    std::string Type;
    std::string State;
    double Earnings;
    std::vector<Cycle> Cycles;
};
