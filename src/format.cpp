#include <string>
#include <iomanip>
#include "format.h"
#include <iostream>
using std::string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) { 
    int hours = 0;
    int minutes = 0;
    int seconds_ = 0;
    std::stringstream stream;

    hours = seconds / 3600;
    minutes = (seconds - (hours * 3600)) / 60;
    seconds_ = seconds - (hours * 3600) - (minutes * 60);

    stream << std::setfill('0') << std::setw(2) << hours << ":" << std::setw(2) << minutes << ":" << std::setw(2) << seconds_;
    return stream.str();
}
