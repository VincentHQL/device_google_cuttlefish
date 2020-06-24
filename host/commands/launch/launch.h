#pragma once

#include <functional>

#include "common/libs/utils/subprocess.h"
#include "host/commands/launch/process_monitor.h"
#include "host/libs/config/cuttlefish_config.h"

int GetHostPort();
bool AdbUsbEnabled(const vsoc::CuttlefishConfig& config);
void ValidateAdbModeFlag(const vsoc::CuttlefishConfig& config);

std::vector <cuttlefish::SharedFD> LaunchKernelLogMonitor(
    const vsoc::CuttlefishConfig& config,
    cuttlefish::ProcessMonitor* process_monitor,
    unsigned int number_of_event_pipes);
void LaunchLogcatReceiverIfEnabled(const vsoc::CuttlefishConfig& config,
                                   cuttlefish::ProcessMonitor* process_monitor);
void LaunchConfigServer(const vsoc::CuttlefishConfig& config,
                        cuttlefish::ProcessMonitor* process_monitor);
bool LaunchVNCServerIfEnabled(const vsoc::CuttlefishConfig& config,
                              cuttlefish::ProcessMonitor* process_monitor,
                              std::function<bool(cuttlefish::MonitorEntry*)> callback);
void LaunchAdbConnectorIfEnabled(cuttlefish::ProcessMonitor* process_monitor,
                                 const vsoc::CuttlefishConfig& config,
                                 cuttlefish::SharedFD adbd_events_pipe);
void LaunchSocketVsockProxyIfEnabled(cuttlefish::ProcessMonitor* process_monitor,
                                 const vsoc::CuttlefishConfig& config);
