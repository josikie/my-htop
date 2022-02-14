#include <string>

#include "format.h"

using std::string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) { 
    int ours = 0;
    int minutes = 0;
    int seconds_ = 0;

    ours = seconds / 3600;
    minutes = (seconds - (ours * 3600)) / 60;
    seconds_ = seconds - (ours * 3600) - (minutes * 60);

    string oursInString = std::to_string(ours);
    string minutesInString = std::to_string(minutes);
    string secondsInString = std::to_string(seconds_);

    string elapsedTime = oursInString + ":" + minutesInString + ":" + secondsInString;
    return elapsedTime;

}