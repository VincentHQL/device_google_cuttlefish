#pragma once

#include <functional>
#include <set>
#include <string>

#include "common/libs/fs/shared_fd.h"
#include "common/libs/utils/subprocess.h"
#include "host/commands/run_cvd/process_monitor.h"
#include "host/libs/config/cuttlefish_config.h"

std::vector <cuttlefish::SharedFD> LaunchKernelLogMonitor(
    const vsoc::CuttlefishConfig& config,
    cuttlefish::ProcessMonitor* process_monitor,
    unsigned int number_of_event_pipes);
void LaunchAdbConnectorIfEnabled(cuttlefish::ProcessMonitor* process_monitor,
                                 const vsoc::CuttlefishConfig& config,
                                 cuttlefish::SharedFD adbd_events_pipe);
void LaunchSocketVsockProxyIfEnabled(cuttlefish::ProcessMonitor* process_monitor,
                                 const vsoc::CuttlefishConfig& config);

struct StreamerLaunchResult {
  bool launched = false;
  std::optional<unsigned int> frames_server_vsock_port;
  std::optional<unsigned int> touch_server_vsock_port;
  std::optional<unsigned int> keyboard_server_vsock_port;
};
StreamerLaunchResult LaunchVNCServer(
    const vsoc::CuttlefishConfig& config,
    cuttlefish::ProcessMonitor* process_monitor,
    std::function<bool(cuttlefish::MonitorEntry*)> callback);

struct TombstoneReceiverPorts {
  std::optional<unsigned int> server_vsock_port;
};
TombstoneReceiverPorts LaunchTombstoneReceiverIfEnabled(
    const vsoc::CuttlefishConfig& config, cuttlefish::ProcessMonitor* process_monitor);

struct ConfigServerPorts {
  std::optional<unsigned int> server_vsock_port;
};
ConfigServerPorts LaunchConfigServer(const vsoc::CuttlefishConfig& config,
                                     cuttlefish::ProcessMonitor* process_monitor);

void LaunchLogcatReceiver(const vsoc::CuttlefishConfig& config,
                          cuttlefish::ProcessMonitor* process_monitor);

StreamerLaunchResult LaunchWebRTC(cuttlefish::ProcessMonitor* process_monitor,
                                  const vsoc::CuttlefishConfig& config);

void LaunchVerhicleHalServerIfEnabled(const vsoc::CuttlefishConfig& config,
                                      cuttlefish::ProcessMonitor* process_monitor);
