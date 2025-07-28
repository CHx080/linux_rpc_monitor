#include "base.h"

void NetMonitor::update(Monitor::MonitorInfo *info) {
  File file("/proc/net/dev");
  file.readLine(nullptr);
  file.readLine(nullptr);
  std::vector<std::string> line;
  auto net_info = info->mutable_net_info();
  while (file.readLine(&line)) {
    auto detail = net_info->Add();
    detail->set_net_name(line[0]);
    auto net_stat = detail->mutable_info();
    net_stat->set_rx_bytes(std::stoull(line[1]));
    net_stat->set_rx_packets(std::stoull(line[2]));
    net_stat->set_rx_errors(std::stoull(line[3]));
    net_stat->set_rx_drops(std::stoull(line[4]));
    net_stat->set_rx_fifo(std::stoull(line[5]));
    net_stat->set_rx_frame(std::stoull(line[6]));
    net_stat->set_rx_compressed(std::stoull(line[7]));
    net_stat->set_rx_multicast(std::stoull(line[8]));

    net_stat->set_tx_bytes(std::stoull(line[9]));
    net_stat->set_tx_packets(std::stoull(line[10]));
    net_stat->set_tx_errors(std::stoull(line[11]));
    net_stat->set_tx_drops(std::stoull(line[12]));
    net_stat->set_tx_fifo(std::stoull(line[13]));
    net_stat->set_tx_colls(std::stoull(line[14]));
    net_stat->set_tx_carrier(std::stoull(line[15]));
    net_stat->set_tx_compressed(std::stoull(line[16]));
    line.clear();
  }
}