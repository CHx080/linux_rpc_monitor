#pragma once
#include "base.h"
class MemMonitor : public GenericMonitor {
public:
  void update(Monitor::MonitorInfo *info) override;
};