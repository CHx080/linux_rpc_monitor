#pragma once
#include "ui.h"
#include <QStandardItemModel>
#include <QTableView>
#include <QVBoxLayout>

class LoadUI : public QWidget, public UI {
public:
  LoadUI(QWidget *parent = nullptr) : QWidget(parent) {
    model.setRowCount(1);
    model.setHorizontalHeaderLabels(
        {"load_1", "load_3", "load_15", "nr_run", "nr_thread"});
    tableView.setModel(&model);
    tableView.setEditTriggers(QAbstractItemView::NoEditTriggers);
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(&tableView);
    setWindowTitle("Cpu Load");
    resize(550, 200);
  }
  void refresh(Monitor::MonitorInfo *info) override {
    auto load_info = info->cpu_load();
    model.setItem(0, 0, new QStandardItem(QString::number(load_info.avg_1())));
    model.setItem(0, 1, new QStandardItem(QString::number(load_info.avg_3())));
    model.setItem(0, 2, new QStandardItem(QString::number(load_info.avg_15())));
    model.setItem(0, 3,
                  new QStandardItem(QString::number(load_info.nr_running())));
    model.setItem(0, 4,
                  new QStandardItem(QString::number(load_info.nr_thread())));
  }

private:
  QStandardItemModel model;
  QTableView tableView;
};