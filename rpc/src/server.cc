#include "cpu_load.h"
#include "cpu_softirq.h"
#include "cpu_stat.h"
#include "mem_info.h"
#include "net_info.h"
#include "service.pb.h"
#include <atomic>
#include <brpc/server.h>
#include <butil/logging.h>
#include <memory>
#include <thread>

class RpcServiceImpl : public Monitor::RpcService {
  enum TAG {
    LOAD,
    STAT,
    SOFTIRQ,
    MEM,
    NET,
    SIZE,
  };

public:
  RpcServiceImpl() {
    monitor_ths.emplace_back([this]() {
      auto load_monitor = std::make_unique<LoadMonitor>();
      while (not this->stop) {
        if (this->handle) {
          load_monitor->update(this->handle);
          done_tag |= (1 << LOAD);
        }
      }
    });
    monitor_ths.emplace_back([this]() {
      auto stat_monitor = std::make_unique<StatMonitor>();
      auto sirq_monitor = std::make_unique<SoftirqMonitor>();
      while (not this->stop) {
        if (this->handle) {
          stat_monitor->update(this->handle);
          done_tag |= (1 << STAT);
          sirq_monitor->update(this->handle);
          done_tag |= (1 << SOFTIRQ);
        }
      }
    });
    monitor_ths.emplace_back([this]() {
      auto mem_monitor = std::make_unique<MemMonitor>();
      while (not this->stop) {
        if (this->handle) {
          mem_monitor->update(this->handle);
          done_tag |= (1 << MEM);
        }
      }
    });
    monitor_ths.emplace_back([this]() {
      auto net_monitor = std::make_unique<NetMonitor>();
      while (not this->stop) {
        if (this->handle) {
          net_monitor->update(this->handle);
          done_tag |= (1 << NET);
        }
      }
    });
  }
  ~RpcServiceImpl() override {
    stop = true;
    for (auto &t : monitor_ths) {
      t.join();
    }
  }
  void GetMonitorInfo(google::protobuf::RpcController *controller,
                      const google::protobuf::Empty *request,
                      Monitor::MonitorInfo *response,
                      ::google::protobuf::Closure *done) override {
    brpc::ClosureGuard guard(done);
    handle = response;
    do {
    } while (done_tag != (1 << SIZE) - 1);
    handle = nullptr;
    done_tag = 0;
  }

private:
  bool stop = false;
  uint8_t done_tag = 0;
  std::atomic<Monitor::MonitorInfo *> handle = nullptr;
  std::vector<std::thread> monitor_ths;
};
class RpcServer {
public:
  RpcServer(int port) {
    server.AddService(new RpcServiceImpl,
                      brpc::ServiceOwnership::SERVER_OWNS_SERVICE);
    //......
    server.Start(port, nullptr);
    server.RunUntilAskedToQuit();
  }
  RpcServer(const RpcServer &) = delete;
  RpcServer &operator=(const RpcServer &) = delete;

private:
  brpc::Server server;
};

int main(int argc, char *argv[]) {
  logging::LoggingSettings settings;
  settings.logging_dest = logging::LoggingDestination::LOG_TO_NONE;
  logging::InitLogging(settings);
  RpcServer instance(atoi(argv[1]));
  return 0;
}