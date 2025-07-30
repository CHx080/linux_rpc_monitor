#include "client.h"
#include "load_ui.hpp"
#include "mem_ui.hpp"
#include "net_ui.hpp"
#include "softirq_ui.hpp"
#include "stat_ui.hpp"
#include <QApplication>
#include <QHBoxLayout>
#include <QMainWindow>
#include <QPushButton>
#include <thread>

int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cout << "Usage : [executable] [ip]:[port]\n";
    exit(EXIT_FAILURE);
  }
  QApplication app(argc, argv);
  QMainWindow window;
  window.setWindowTitle("Watch");
  window.setFixedSize(550, 150);

  QWidget *centralWidget = new QWidget(&window);
  window.setCentralWidget(centralWidget);
  QHBoxLayout *hLayout = new QHBoxLayout(centralWidget);
  centralWidget->setLayout(hLayout);

  QPushButton *buttons[] = {
      new QPushButton("CPU Load"),    new QPushButton("CPU Stat"),
      new QPushButton("CPU SoftIRQ"), new QPushButton("Memory"),
      new QPushButton("Network"),     new QPushButton("Exit")};
  for (int i = 0; i < 6; ++i) {
    hLayout->addWidget(buttons[i]);
  }

  UI *ui_obj[] = {
      new LoadUI, new StatUI, new SirqUI, new MemUI, new NetUI,
  };

  QObject::connect(buttons[0], &QPushButton::clicked,
                   [ui_obj]() { ui_obj[0]->show(); });
  QObject::connect(buttons[1], &QPushButton::clicked,
                   [ui_obj]() { ui_obj[1]->show(); });
  QObject::connect(buttons[2], &QPushButton::clicked,
                   [ui_obj]() { ui_obj[2]->show(); });
  QObject::connect(buttons[3], &QPushButton::clicked,
                   [ui_obj]() { ui_obj[3]->show(); });
  QObject::connect(buttons[4], &QPushButton::clicked,
                   [ui_obj]() { ui_obj[4]->show(); });
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
      std::this_thread::sleep_for(std::chrono::seconds(1));
    }
  });
  loop.detach();

  return app.exec();
}