#include <dirent.h>
#include <unistd.h>
#include <sstream>
#include <string>
#include <vector>

#include "linux_parser.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;

// findValueByKey() generic function for search a value with corresponding key
template <typename T> 
T findValueByKey(string const &key, string const &file){
  T value;
  string line; 
  string k;

  std::ifstream stream(LinuxParser::kProcDirectory + file);
  if(stream.is_open()){
    while(std::getline(stream, line)){
      std::istringstream linestream(line);
      while(linestream >> k >> value){
        if(k == key){
          return value;
        }
      }
    }
  }
  return value;
};

// findValue() generic function for take the first value of file
template <typename T>
T findValue(string const &file){
  T value;
  string line;
  std::ifstream stream(LinuxParser::kProcDirectory + file);
  if(stream.is_open()){
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> value;
  }
  return value;
}

string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == filterPrettyName) {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

string LinuxParser::Kernel() {
  string os, kernel, version;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

float LinuxParser::MemoryUtilization() { 
  string key;
  string value;
  float memTotal = findValueByKey<float>(filterMemTotal, kMeminfoFilename);
  float memFree = findValueByKey<float>(filterMemFree, kMeminfoFilename);
  return (memTotal - memFree)/memTotal;
}

long LinuxParser::UpTime() {
  long uptime = findValue<long>(kUptimeFilename);
  return uptime;
}

int LinuxParser::TotalProcesses() { 
    int totalProccess = findValueByKey<int>(filterProcesses, kStatFilename);
    return totalProccess;
}

int LinuxParser::RunningProcesses() {
  int totalRunning = findValueByKey<int>(filterProcsRunning, kStatFilename);
  return totalRunning;
}

string LinuxParser::Command(int pid) { 
  string lineCommand;

  std::ifstream stream(kProcDirectory + std::to_string(pid) + kCmdlineFilename);
  if(stream.is_open()){
    std::getline(stream, lineCommand);
  }

  return lineCommand;
}

string LinuxParser::Ram(int pid) { 
  string filename = std::to_string(pid) + kStatusFilename;
  // Using VmRSS instead VmSize for the exact Physical Ram, link => https://man7.org/linux/man-pages/man5/proc.5.html.
  int ram = findValueByKey<int>(filterVmRSS, filename);
  ram /= 1000;
  return std::to_string(ram);
}

string LinuxParser::Uid(int pid) { 
  string filename = std::to_string(pid) + kStatusFilename;
  string line;
  string uid = findValueByKey<string>(filterUid, filename);
  return uid;
}

string LinuxParser::User(int pid) { 
  string number;
  string name;
  string x;
  string line;
  string uid = LinuxParser::Uid(pid);
  std::ifstream stream(kPasswordPath);
  if(stream.is_open()){
    while(std::getline(stream, line)){
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      linestream >> name >> x >> number;
      if(number == uid){
        return name;
      }
    }
  }
  return name;
}

long LinuxParser::UpTime(int pid) {
  long uptime;
  float hertz = sysconf(_SC_CLK_TCK);
  string line;
  int value, starttime;
  std::ifstream stream(kProcDirectory + std::to_string(pid) + kStatFilename);
  if(stream.is_open()){
    std::getline(stream, line);
    std::istringstream linestream(line);
    for(int i = 1; i <= 22; i++){
      linestream >> value;
      if(i == 22){
        starttime = value;
      }
    }
    uptime =  starttime / hertz;
  }

  return uptime;
}
