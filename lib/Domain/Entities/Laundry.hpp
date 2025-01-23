#pragma once
#include <vector>
#include <string>
#include "Machine.hpp"

struct Laundry
{
    int Id;
    int ProprietorId;
    std::string Name;
    std::string Address;
    double Earnings;
    std::vector<Machine> Machines;
};