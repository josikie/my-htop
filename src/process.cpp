#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "process.h"
#include "linux_parser.h"

using std::string;
using std::to_string;
using std::vector;

// TODO: Return this process's ID
int Process::Pid() { return pid_;}

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() { 
  long uptime = LinuxParser::UpTime();
  float hertz = sysconf(_SC_CLK_TCK);
  string line;
  int total_time;
  int seconds;
  float cpu_usage;
  vector<string> number;
  std::ifstream stream(LinuxParser::kProcDirectory + std::to_string(pid_) + LinuxParser::kStatFilename);
  if(stream.is_open()){
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> number[0] >> number[1] >> number[2] >> number[3] >> number[4] >> number[5] 
    >> number[6] >> number[7] >> number[8] >> number[9] >> number[10] >> number[11] >> number[12]
    >> number[13] >> number[14] >> number[15] >> number[16] >> number[17] >> number[18] >> number[19]
    >> number[20] >> number[21];
    total_time = stoi(number[13]) + stoi(number[14]);
    total_time = total_time + stoi(number[15]) + stoi(number[16]);
    seconds = uptime - (stoi(number[21]) / hertz);
    cpu_usage = 100 * ((total_time / hertz) / seconds);
  }
  cpuUtilization = cpu_usage;
  return cpu_usage;
}

// TODO: Return the command that generated this process
string Process::Command() { 
  return LinuxParser::Command(pid_);
}

// TODO: Return this process's memory utilization
string Process::Ram() { 
  return LinuxParser::Ram(pid_);
}

// TODO: Return the user (name) that generated this process
string Process::User() { 
  return LinuxParser::User(pid_);
}

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { 
  return LinuxParser::UpTime(pid_);
}

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a) const { 
  return this->cpuUtilization < a.cpuUtilization;
}