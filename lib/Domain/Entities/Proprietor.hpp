#pragma once
#include <vector>
#include "Laundry.hpp"

struct Proprietor
{
    int Id;
    std::string Name;
    std::string Email;
    double TotalEarnings;
    std::vector<Laundry> Laundries;
};