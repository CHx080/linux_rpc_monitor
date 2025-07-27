#pragma once
#include "service.pb.h"
class UI {
public:
  virtual void refresh(Monitor::MonitorInfo *info) = 0;
};