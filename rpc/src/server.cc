#include "cpu_load.h"
#include "cpu_softirq.h"
#include "cpu_stat.h"
#include "mem_info.h"
#include "net_info.h"
#include "service.pb.h"
#include <brpc/server.h>
#include <butil/logging.h>
#include <thread>

class RpcServiceImpl : public Monitor::RpcService {
public:
  void GetMonitorInfo(google::protobuf::RpcController *controller,
                      const google::protobuf::Empty *request,
                      Monitor::MonitorInfo *response,
                      ::google::protobuf::Closure *done) override {
    brpc::ClosureGuard guard(done);
    std::thread t0([response, this]() { this->load_monitor.update(response); });
    std::thread t1([response, this]() { this->mem_monitor.update(response); });
    std::thread t2([response, this]() { this->net_monitor.update(response); });
    std::thread t3([response, this]() {
      this->stat_monitor.update(response); // stat必须先于sriq检测
      this->sirq_monitor.update(response);
    });
    t0.join();
    t1.join();
    t2.join();
    t3.join();
  }

private:
  LoadMonitor load_monitor;
  StatMonitor stat_monitor;
  SoftirqMonitor sirq_monitor;
  MemMonitor mem_monitor;
  NetMonitor net_monitor;
};
class RpcServer {
public:
  RpcServer(int port) {
    server.AddService(new RpcServiceImpl,
                      brpc::ServiceOwnership::SERVER_OWNS_SERVICE);
    //......
    if (not server.Start(port, nullptr)) {
      std::cerr << "fail start,check the port number!\n";
      exit(EXIT_FAILURE);
    }
    server.RunUntilAskedToQuit();
  }
  RpcServer(const RpcServer &) = delete;
  RpcServer &operator=(const RpcServer &) = delete;

private:
  brpc::Server server;
};

int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cerr << "Usage: [executable] [port] \n";
    exit(EXIT_FAILURE);
  }
  logging::LoggingSettings settings;
  settings.logging_dest = logging::LoggingDestination::LOG_TO_NONE;
  logging::InitLogging(settings);
  RpcServer instance(atoi(argv[1]));
  return EXIT_FAILURE;
}