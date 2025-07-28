#pragma once
#include "service.pb.h"
#include "ui.h"
#include <QStandardItemModel>
#include <QTableView>
#include <QVBoxLayout>
#include <unordered_map>
#include <unordered_set>

class NetUI : public UI {
  enum Field {
    DEV,
    R_BYTES,
    R_PACKETS,
    R_ERRS,
    R_DROPS,
    R_FIFO,
    R_FRAME,
    R_COMPRSS,
    R_MUL,
    PADDING,
    W_BYTES,
    W_PACKETS,
    W_ERRS,
    W_DROPS,
    W_FIFO,
    W_COLLS,
    W_CARRIER,
    W_COMPRESS,
  };

public:
  NetUI(QWidget *parent = nullptr) : UI(parent) {
    model.setHorizontalHeaderLabels(
        {"dev", "bytes", "packets", "errs", "drop", "fifo", "frame",
         "compressed", "multicast", "rx<--->tx", "bytes", "packets", "errs",
         "drop", "fifo", "colls", "carrier", "compressed"});
    tableView.setModel(&model);
    tableView.setEditTriggers(QAbstractItemView::NoEditTriggers);
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(&tableView);
    setWindowTitle("Net");
    resize(1000, 500);
  }

  void refresh(Monitor::MonitorInfo *info) override {
    auto net_info = info->net_info();
    int num = net_info.size();
    for (int i = 0; i < num; ++i) {
      auto &item = net_info.Get(i);
      auto &name = item.net_name();
      auto &detail = item.info();
      if (not devices.count(name)) [[unlikely]] {
        model.appendRow({
            new QStandardItem(name.c_str()),
            new QStandardItem(QString::number(detail.rx_bytes())),
            new QStandardItem(QString::number(detail.rx_packets())),
            new QStandardItem(QString::number(detail.rx_errors())),
            new QStandardItem(QString::number(detail.rx_drops())),
            new QStandardItem(QString::number(detail.rx_fifo())),
            new QStandardItem(QString::number(detail.rx_frame())),
            new QStandardItem(QString::number(detail.rx_compressed())),
            new QStandardItem(QString::number(detail.rx_multicast())),
            new QStandardItem(""),
            new QStandardItem(QString::number(detail.tx_bytes())),
            new QStandardItem(QString::number(detail.tx_packets())),
            new QStandardItem(QString::number(detail.tx_errors())),
            new QStandardItem(QString::number(detail.tx_drops())),
            new QStandardItem(QString::number(detail.tx_fifo())),
            new QStandardItem(QString::number(detail.tx_colls())),
            new QStandardItem(QString::number(detail.tx_carrier())),
            new QStandardItem(QString::number(detail.tx_compressed())),
        });
        idx[name] = model.rowCount() - 1;
        devices.insert(name);
      } else {
        int id = idx[name];
        model.setItem(id, R_BYTES,
                      new QStandardItem(QString::number(detail.rx_bytes())));
        model.setItem(id, R_PACKETS,
                      new QStandardItem(QString::number(detail.rx_packets())));
        model.setItem(id, R_ERRS,
                      new QStandardItem(QString::number(detail.rx_errors())));
        model.setItem(id, R_DROPS,
                      new QStandardItem(QString::number(detail.rx_drops())));
        model.setItem(id, R_FIFO,
                      new QStandardItem(QString::number(detail.rx_fifo())));
        model.setItem(id, R_FRAME,
                      new QStandardItem(QString::number(detail.rx_frame())));
        model.setItem(
            id, R_COMPRSS,
            new QStandardItem(QString::number(detail.rx_compressed())));
        model.setItem(
            id, R_MUL,
            new QStandardItem(QString::number(detail.rx_multicast())));

        model.setItem(id, W_BYTES,
                      new QStandardItem(QString::number(detail.tx_bytes())));
        model.setItem(id, W_PACKETS,
                      new QStandardItem(QString::number(detail.tx_packets())));
        model.setItem(id, W_ERRS,
                      new QStandardItem(QString::number(detail.tx_errors())));
        model.setItem(id, W_DROPS,
                      new QStandardItem(QString::number(detail.tx_drops())));
        model.setItem(id, W_FIFO,
                      new QStandardItem(QString::number(detail.tx_fifo())));
        model.setItem(id, W_COLLS,
                      new QStandardItem(QString::number(detail.tx_colls())));
        model.setItem(id, W_CARRIER,
                      new QStandardItem(QString::number(detail.tx_carrier())));
        model.setItem(
            id, W_COMPRESS,
            new QStandardItem(QString::number(detail.tx_compressed())));
      }
    }
  }

private:
  std::unordered_set<std::string> devices;
  std::unordered_map<std::string, int> idx;
  QStandardItemModel model;
  QTableView tableView;
};