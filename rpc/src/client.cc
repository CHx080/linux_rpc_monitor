#include "client.h"
#include "service.pb.h"
#include <brpc/channel.h>
#include <brpc/controller.h>
#include <memory>

RpcClient::RpcClient(const char *_socket) {
  channel.Init(_socket, nullptr);
  stub = std::make_unique<Monitor::RpcService_Stub>(&channel);
}

bool RpcClient::getMonitorInfo(Monitor::MonitorInfo *info) {
  brpc::Controller controller;
  google::protobuf::Empty empty_request;
  stub->GetMonitorInfo(&controller, &empty_request, info, nullptr);
  return controller.Failed() ? false : true;
}

// int main(int argc, char *argv[]) {
//   RpcClient client(argv[1]);
//   while (true) {
//     Monitor::MonitorInfo res;
//     bool ok = client.getMonitorInfo(&res);
//     if (not ok) {
//       break;
//     }
//     //...

//     std::this_thread::sleep_for(std::chrono::seconds(1));
//   }
//   return 0;
// }