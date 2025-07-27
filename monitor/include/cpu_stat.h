#pragma once
#include "base.h"

class StatMonitor : public GenericMonitor {
public:
  StatMonitor();
  void update(Monitor::MonitorInfo *info) override;

private:
  using ull = unsigned long long;
  std::vector<std::vector<ull>> recent;
  long num_cores;
};