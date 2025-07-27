#pragma once
#include "base.h"
class SoftirqMonitor : public GenericMonitor {
public:
  SoftirqMonitor();
  void update(Monitor::MonitorInfo *info) override;

private:
  long num_cores;
};