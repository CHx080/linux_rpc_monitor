#include "client.h"
#include "load_ui.hpp"
#include "mem_ui.hpp"
#include "net_ui.hpp"
#include "softirq_ui.hpp"
#include "stat_ui.hpp"
#include <QApplication>
#include <QHBoxLayout>
#include <QMainWindow>
#include <QMutex>
#include <QPushButton>
#include <QThread>
#include <QVector>
#include <thread>
int main(int argc, char *argv[]) {
  QApplication app(argc, argv);
  QMainWindow window;
  window.setWindowTitle("Watch");
  window.setFixedSize(550, 150);
  window.setWindowFlags(window.windowFlags() | Qt::FramelessWindowHint);

  QWidget *centralWidget = new QWidget(&window);
  window.setCentralWidget(centralWidget);

  QHBoxLayout *hLayout = new QHBoxLayout(centralWidget);
  QPushButton *buttons[] = {
      new QPushButton("CPU Load"),    new QPushButton("CPU Stat"),
      new QPushButton("CPU SoftIRQ"), new QPushButton("Memory"),
      new QPushButton("Network"),     new QPushButton("Exit")};
  for (int i = 0; i < 6; ++i) {
    hLayout->addWidget(buttons[i]);
  }
  centralWidget->setLayout(hLayout);

  QVector<UI *> ui_obj;
  QMutex mtx;

  QObject::connect(buttons[0], &QPushButton::clicked, [&mtx, &ui_obj]() {
    LoadUI *loadUI = new LoadUI;
    {
      QMutexLocker<QMutex> guard(&mtx);
      ui_obj.emplace_back(loadUI);
    }
    loadUI->setAttribute(Qt::WA_DeleteOnClose);
    loadUI->show();
  });
  QObject::connect(buttons[1], &QPushButton::clicked, [&mtx, &ui_obj]() {
    StatUI *statUI = new StatUI;
    {
      QMutexLocker<QMutex> guard(&mtx);
      ui_obj.emplace_back(statUI);
    }
    statUI->setAttribute(Qt::WA_DeleteOnClose);
    statUI->show();
  });
  QObject::connect(buttons[2], &QPushButton::clicked, [&mtx, &ui_obj]() {
    SirqUI *sirqUI = new SirqUI;
    {
      QMutexLocker<QMutex> guard(&mtx);
      ui_obj.emplace_back(sirqUI);
    }
    sirqUI->setAttribute(Qt::WA_DeleteOnClose);
    sirqUI->show();
  });
  QObject::connect(buttons[3], &QPushButton::clicked, [&mtx, &ui_obj]() {
    MemUI *memUI = new MemUI;
    {
      QMutexLocker<QMutex> guard(&mtx);
      ui_obj.emplace_back(memUI);
    }
    memUI->setAttribute(Qt::WA_DeleteOnClose);
    memUI->show();
  });

  QObject::connect(buttons[4], &QPushButton::clicked, [&mtx, &ui_obj]() {
    NetUI *netUI = new NetUI;
    {
      QMutexLocker<QMutex> guard(&mtx);
      ui_obj.emplace_back(netUI);
    }
    netUI->setAttribute(Qt::WA_DeleteOnClose);
    netUI->show();
  });

  QObject::connect(buttons[5], &QPushButton::clicked,
                   []() { exit(EXIT_SUCCESS); });
  window.show();
  std::thread loop([&ui_obj, argv]() {
    RpcClient client(argv[1]);
    while (true) {
      Monitor::MonitorInfo info;
      client.getMonitorInfo(&info);
      for (UI *it : ui_obj) {
        it->refresh(&info);
      }
      QThread::sleep(1);
    }
  });
  loop.detach();
  return app.exec();
}