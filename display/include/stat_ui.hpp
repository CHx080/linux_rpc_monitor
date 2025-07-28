#pragma once
#include "service.pb.h"
#include "ui.h"
#include <QStandardItemModel>
#include <QTableView>
#include <QVBoxLayout>
#include <unordered_map>
#include <unordered_set>

class StatUI : public UI {
  enum Field { CPU, USER, NICE, SYS, IDLE, IOWAIT, IRQ, SOFTIRQ, STEAL };

public:
  StatUI(QWidget *parent = nullptr) : UI(parent) {
    model.setHorizontalHeaderLabels({"CPU", "User", "Nice", "System", "Idle",
                                     "IOWait", "IRQ", "SoftIRQ", "Steal"});
    tableView.setModel(&model);
    tableView.setEditTriggers(QAbstractItemView::NoEditTriggers);
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(&tableView);
    setWindowTitle("CPU Stat");
    resize(800, 400);
  }

  void refresh(Monitor::MonitorInfo *info) override {
    auto &cpu_stats = info->cpu_info();
    int num = cpu_stats.size();
    for (int i = 0; i < num; ++i) {
      auto &cpuinfo = cpu_stats.Get(i);
      auto &name = cpuinfo.cpu_name();
      auto &stat = cpuinfo.cpu_stat();
      if (not devices.count(name)) [[unlikely]] {
        model.appendRow(
            {new QStandardItem(name.c_str()),
             new QStandardItem(QString::number(stat.user(), 'f', 2)),
             new QStandardItem(QString::number(stat.nice(), 'f', 2)),
             new QStandardItem(QString::number(stat.sys(), 'f', 2)),
             new QStandardItem(QString::number(stat.idle(), 'f', 2)),
             new QStandardItem(QString::number(stat.iowait(), 'f', 2)),
             new QStandardItem(QString::number(stat.irq(), 'f', 2)),
             new QStandardItem(QString::number(stat.softirq(), 'f', 2)),
             new QStandardItem(QString::number(stat.steal(), 'f', 2))});
        idx[name] = model.rowCount() - 1;
        devices.insert(name);
      } else {
        int id = idx[name];
        model.setItem(id, USER,
                      new QStandardItem(QString::number(stat.user(), 'f', 2)));
        model.setItem(id, NICE,
                      new QStandardItem(QString::number(stat.nice(), 'f', 2)));
        model.setItem(id, SYS,
                      new QStandardItem(QString::number(stat.sys(), 'f', 2)));
        model.setItem(id, IDLE,
                      new QStandardItem(QString::number(stat.idle(), 'f', 2)));
        model.setItem(
            id, IOWAIT,
            new QStandardItem(QString::number(stat.iowait(), 'f', 2)));
        model.setItem(id, IRQ,
                      new QStandardItem(QString::number(stat.irq(), 'f', 2)));
        model.setItem(
            id, SOFTIRQ,
            new QStandardItem(QString::number(stat.softirq(), 'f', 2)));
        model.setItem(id, STEAL,
                      new QStandardItem(QString::number(stat.steal(), 'f', 2)));
      }
    }
  }

private:
  std::unordered_set<std::string> devices;
  std::unordered_map<std::string, int> idx;
  QStandardItemModel model;
  QTableView tableView;
};