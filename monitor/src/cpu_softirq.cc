#include "base.h"
#include <unistd.h>

#define set_sirq(Name)                                                         \
  file.readLine(&line);                                                        \
  for (int i = 1; i <= num_cores; ++i) {                                       \
    auto sirq = info->mutable_cpu_info()->Mutable(i)->mutable_cpu_sirq();      \
    sirq->set_##Name(stoull(line[i]));                                         \
  }                                                                            \
  line.clear()

SoftirqMonitor::SoftirqMonitor() { num_cores = sysconf(_SC_NPROCESSORS_ONLN); }

void SoftirqMonitor::update(Monitor::MonitorInfo *info) {
  File file("/proc/softirqs");
  file.readLine(nullptr);
  std::vector<std::string> line;
  set_sirq(hi);
  set_sirq(timer);
  set_sirq(net_tx);
  set_sirq(net_rx);
  set_sirq(block);
  set_sirq(irq_poll);
  set_sirq(tasklet);
  set_sirq(sched);
  set_sirq(hr_timer);
  set_sirq(rcu);
}