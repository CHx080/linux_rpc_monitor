#pragma once
#include "service.pb.h"
#include <brpc/channel.h>
#include <memory>
class RpcClient {
public:
  RpcClient(const char *_socket);
  RpcClient(const RpcClient &) = delete;
  RpcClient &operator=(const RpcClient &) = delete;
  bool getMonitorInfo(Monitor::MonitorInfo *info);

private:
  brpc::Channel channel;
  std::unique_ptr<Monitor::RpcService_Stub> stub;
};