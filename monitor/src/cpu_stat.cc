#include "cpu_stat.h"
#include <string>
#include <unistd.h>

StatMonitor::StatMonitor() {
  num_cores = sysconf(_SC_NPROCESSORS_ONLN);
  recent.resize(num_cores + 1);
  for (int i = 0; i <= num_cores; ++i) {
    recent[i].resize(8);
  }
}
void StatMonitor::update(Monitor::MonitorInfo *info) {
  File file("/proc/stat");

  std::vector<std::string> line;
  for (int i = 0; i <= num_cores; ++i) { // i==0表示总cpu
    file.readLine(&line);
    ull us_delta = std::stoull(line[1]) - recent[i][0];
    recent[i][0] += us_delta;
    ull ni_delta = std::stoull(line[2]) - recent[i][1];
    recent[i][1] += ni_delta;
    ull sys_delta = std::stoull(line[3]) - recent[i][2];
    recent[i][2] += sys_delta;
    ull idle_delta = std::stoull(line[4]) - recent[i][3];
    recent[i][3] += idle_delta;
    ull iow_delta = std::stoull(line[5]) - recent[i][4];
    recent[i][4] += iow_delta;
    ull irq_delta = std::stoull(line[6]) - recent[i][5];
    recent[i][5] += irq_delta;
    ull sirq_delta = std::stoull(line[7]) - recent[i][6];
    recent[i][6] += sirq_delta;
    ull st_delta = std::stoull(line[8]) - recent[i][7];
    recent[i][7] += st_delta;

    ull totol_delta = us_delta + ni_delta + sys_delta + idle_delta + iow_delta +
                      irq_delta + sirq_delta + st_delta;

    auto cpu_info = info->mutable_cpu_info()->Add();
    cpu_info->set_cpu_name(line[0]);
    auto stat = cpu_info->mutable_cpu_stat();
    stat->set_user(100.00 * us_delta / totol_delta);
    stat->set_nice(100.00 * ni_delta / totol_delta);
    stat->set_sys(100.00 * sys_delta / totol_delta);
    stat->set_idle(100.00 * idle_delta / totol_delta);
    stat->set_iowait(100.00 * iow_delta / totol_delta);
    stat->set_irq(100.00 * irq_delta / totol_delta);
    stat->set_softirq(100.00 * sirq_delta / totol_delta);
    stat->set_steal(100.00 * st_delta / totol_delta);
    line.clear();
  }
}