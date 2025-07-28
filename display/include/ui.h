#pragma once
#include "service.pb.h"
#include <QWidget>
class UI : public QWidget {
public:
  UI(QWidget *parent = nullptr) : QWidget(parent) {}
  virtual void refresh(Monitor::MonitorInfo *info) = 0;
};