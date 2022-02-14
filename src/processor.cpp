#include "processor.h"
#include "linux_parser.h"
// TODO: Return the aggregate CPU utilization
float Processor::Utilization() { 
  // try with OOP style
  return LinuxParser::ActiveJiffies() / (LinuxParser::ActiveJiffies() + LinuxParser::IdleJiffies());
  // float activeJiffies;
  // float idleJiffies;
  // float jiffies;
  // std::ifstream stream(LinuxParser::kProcDirectory + LinuxParser::kStatFilename);
  // if(stream.is_open()){
  //   std::getline(stream, line);
  //   std::istringstream linestream(line);
  //   linestream >> cpu >> user >> nice >> system >> idle >> iowait >> irq >> sortirq >> steal;
  // }
  
  // activeJiffies = user + nice + system + irq + sortirq + steal;
  // idleJiffies = idle + iowait;

  // jiffies = activeJiffies + idleJiffies;
  // return activeJiffies/idleJiffies;
}