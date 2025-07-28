#include "base.h"

void LoadMonitor::update(Monitor::MonitorInfo *info) {
  File file("/proc/loadavg");
  std::vector<std::string> line;
  auto load = info->mutable_cpu_load();
  file.readLine(&line);
  load->set_avg_1(std::stod(line[0]));
  load->set_avg_3(std::stod(line[1]));
  load->set_avg_15(std::stod(line[2]));
  auto &sv = line[3];
  size_t pos = sv.find('/');
  load->set_nr_running(std::stoull(sv.substr(0, pos)));
  load->set_nr_thread(std::stoull(sv.substr(pos + 1)));
  line.clear();
}