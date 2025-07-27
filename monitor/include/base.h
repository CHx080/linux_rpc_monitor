#pragma once
#include "service.pb.h"
#include "util.h"
class GenericMonitor {
public:
  GenericMonitor() = default;
  GenericMonitor(const GenericMonitor &) = delete;
  GenericMonitor &operator=(const GenericMonitor &) = delete;
  virtual void update(Monitor::MonitorInfo *info) = 0;
};