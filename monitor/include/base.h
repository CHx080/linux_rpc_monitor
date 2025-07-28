#pragma once
#include "service.pb.h"
#include "util.h"
class GenericMonitor {
public:
  GenericMonitor() = default;
  virtual ~GenericMonitor() = default;
  GenericMonitor(const GenericMonitor &) = delete;
  GenericMonitor &operator=(const GenericMonitor &) = delete;
  virtual void update(Monitor::MonitorInfo *info) = 0;
};

class LoadMonitor : public GenericMonitor {
public:
  void update(Monitor::MonitorInfo *info) override;
};

class SoftirqMonitor : public GenericMonitor {
public:
  SoftirqMonitor();
  void update(Monitor::MonitorInfo *info) override;

private:
  long num_cores;
};

class StatMonitor : public GenericMonitor {
public:
  StatMonitor();
  void update(Monitor::MonitorInfo *info) override;

private:
  using ull = unsigned long long;
  std::vector<std::vector<ull>> recent;
  long num_cores;
};

class MemMonitor : public GenericMonitor {
public:
  void update(Monitor::MonitorInfo *info) override;
};

class NetMonitor : public GenericMonitor {
public:
  void update(Monitor::MonitorInfo *info) override;
};