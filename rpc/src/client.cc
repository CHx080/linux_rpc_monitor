#include "client.h"
#include "service.pb.h"
#include <brpc/channel.h>
#include <brpc/controller.h>
#include <memory>

RpcClient::RpcClient(const char *_socket) {
  if (channel.Init(_socket, nullptr) != 0) {
    std::cout << "connect failed !\n";
    exit(EXIT_FAILURE);
  }
  stub = std::make_unique<Monitor::RpcService_Stub>(&channel);
}

bool RpcClient::getMonitorInfo(Monitor::MonitorInfo *info) {
  brpc::Controller controller;
  google::protobuf::Empty empty_request;
  stub->GetMonitorInfo(&controller, &empty_request, info, nullptr);
  return controller.Failed() ? false : true;
}
