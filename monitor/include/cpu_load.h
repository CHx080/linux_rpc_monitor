#pragma once
#include "base.h"

class LoadMonitor : public GenericMonitor {
public:
  void update(Monitor::MonitorInfo *info) override;
};