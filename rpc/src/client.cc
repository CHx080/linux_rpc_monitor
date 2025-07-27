#include "client.h"
#include "service.pb.h"
#include <brpc/channel.h>
#include <brpc/controller.h>
#include <memory>
#include <thread>

RpcClient::RpcClient(const char *_socket) {
  channel.Init(_socket, nullptr);
  stub = std::make_unique<Monitor::RpcService_Stub>(&channel);
}

void RpcClient::getMonitorInfo(Monitor::MonitorInfo *info) {
  brpc::Controller controller;
  google::protobuf::Empty empty_request;
  stub->GetMonitorInfo(&controller, &empty_request, info, nullptr);
}

int main(int argc, char *argv[]) {
  RpcClient client(argv[1]);
  while (true) {
    Monitor::MonitorInfo res;
    client.getMonitorInfo(&res);
    auto load = res.cpu_load();
    std::cout << load.avg_1() << ' ' << load.avg_3() << ' ' << load.avg_15()
              << ' ' << load.nr_running() << ' ' << load.nr_thread()
              << std::endl;
    auto mem = res.mem_info();
    std::cout << mem.active() << ' ' << mem.active_anon() << ' '
              << mem.mem_free() << std::endl;

    std::this_thread::sleep_for(std::chrono::seconds(1));
  }
  return 0;
}