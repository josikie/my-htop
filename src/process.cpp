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
float Process::CpuUtilization() const{ 
  long uptime = LinuxParser::UpTime();
  float hertz = sysconf(_SC_CLK_TCK);
  string line;
  string value;
  int total_time, utime, stime, cutime, cstime, starttime;
  int seconds;
  float cpu_usage;
  std::ifstream stream(LinuxParser::kProcDirectory + std::to_string(pid_) + LinuxParser::kStatFilename);
  if(stream.is_open()){
    std::getline(stream, line);
    std::istringstream linestream(line);
    for(int i = 1; i <= 22; i++){
      linestream >> value;
      if(i == 14){
        utime = stoi(value);
      }else if(i == 15){
        stime = stoi(value);
      }else if(i == 16){
        cutime = stoi(value);
      }else if(i == 17){
        cstime = stoi(value);
      }else if(i == 22){
        starttime = stoi(value);
      }
    }
    total_time = utime + stime;
    total_time = total_time + cutime + cstime;
    seconds = uptime - starttime / hertz;
    cpu_usage = 100 * ((total_time / hertz) / seconds);
  }
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
  return a.CpuUtilization() < this->CpuUtilization();
}