#pragma once
#include "service.pb.h"
#include "ui.h"
#include <QStandardItemModel>
#include <QTableView>
#include <QVBoxLayout>
#include <unordered_map>
#include <unordered_set>

class SirqUI : public UI {
  enum Field {
    CPU,
    HI,
    TIMER,
    NET_TX,
    NET_RX,
    BLOCK,
    IRQ_POLL,
    TASKLET,
    SCHED,
    HR_TIMER,
    RCU
  };

public:
  SirqUI(QWidget *parent = nullptr) : UI(parent) {
    model.setHorizontalHeaderLabels({"CPU", "HI", "Timer", "Net TX", "Net RX",
                                     "Block", "IRQ Poll", "Tasklet", "Sched",
                                     "HR Timer", "RCU"});
    tableView.setModel(&model);
    tableView.setEditTriggers(QAbstractItemView::NoEditTriggers);
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(&tableView);
    setWindowTitle("SoftIRQ Stat");
    resize(1200, 600);
  }

  void refresh(Monitor::MonitorInfo *info) override {
    auto &softirq_sirqs = info->cpu_info();
    int num = softirq_sirqs.size();

    for (int i = 1; i < num; ++i) {
      auto &cpuinfo = softirq_sirqs.Get(i);
      auto &cpu_name = cpuinfo.cpu_name();
      auto &sirq = cpuinfo.cpu_sirq();
      if (!devices.count(cpu_name)) [[unlikely]] {
        model.appendRow({new QStandardItem(cpu_name.c_str()),
                         new QStandardItem(QString::number(sirq.hi())),
                         new QStandardItem(QString::number(sirq.timer())),
                         new QStandardItem(QString::number(sirq.net_tx())),
                         new QStandardItem(QString::number(sirq.net_rx())),
                         new QStandardItem(QString::number(sirq.block())),
                         new QStandardItem(QString::number(sirq.irq_poll())),
                         new QStandardItem(QString::number(sirq.tasklet())),
                         new QStandardItem(QString::number(sirq.sched())),
                         new QStandardItem(QString::number(sirq.hr_timer())),
                         new QStandardItem(QString::number(sirq.rcu()))});
        idx[cpu_name] = model.rowCount() - 1;
        devices.insert(cpu_name);
      } else {
        int id = idx[cpu_name];
        model.setItem(id, HI, new QStandardItem(QString::number(sirq.hi())));
        model.setItem(id, TIMER,
                      new QStandardItem(QString::number(sirq.timer())));
        model.setItem(id, NET_TX,
                      new QStandardItem(QString::number(sirq.net_tx())));
        model.setItem(id, NET_RX,
                      new QStandardItem(QString::number(sirq.net_rx())));
        model.setItem(id, BLOCK,
                      new QStandardItem(QString::number(sirq.block())));
        model.setItem(id, IRQ_POLL,
                      new QStandardItem(QString::number(sirq.irq_poll())));
        model.setItem(id, TASKLET,
                      new QStandardItem(QString::number(sirq.tasklet())));
        model.setItem(id, SCHED,
                      new QStandardItem(QString::number(sirq.sched())));
        model.setItem(id, HR_TIMER,
                      new QStandardItem(QString::number(sirq.hr_timer())));
        model.setItem(id, RCU, new QStandardItem(QString::number(sirq.rcu())));
      }
    }
  }

private:
  std::unordered_set<std::string> devices;
  std::unordered_map<std::string, int> idx;
  QStandardItemModel model;
  QTableView tableView;
};