#pragma once
#include "base.h"
class NetMonitor : public GenericMonitor {
public:
  void update(Monitor::MonitorInfo *info) override;
};