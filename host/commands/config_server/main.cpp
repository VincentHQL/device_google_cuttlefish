/*
 * Copyright (C) 2019 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <common/libs/device_config/device_config.h>
#include <gflags/gflags.h>
#include <glog/logging.h>

#include "common/libs/fs/shared_fd.h"
#include "host/libs/config/cuttlefish_config.h"

DEFINE_int32(
    server_fd, -1,
    "File descriptor to an already created vsock server. If negative a new "
    "server will be created at the port specified on the config file");

int main(int argc, char** argv) {
  ::android::base::InitLogging(argv, android::base::StderrLogger);
  google::ParseCommandLineFlags(&argc, &argv, true);

  auto config = vsoc::CuttlefishConfig::Get();

  cuttlefish::SharedFD server_fd;
  if (FLAGS_server_fd < 0) {
    unsigned int port = config->config_server_port();
    server_fd = cuttlefish::SharedFD::VsockServer(port, SOCK_STREAM);
  } else {
    server_fd = cuttlefish::SharedFD::Dup(FLAGS_server_fd);
    close(FLAGS_server_fd);
  }

  CHECK(server_fd->IsOpen()) << "Error creating or inheriting logcat server: "
                             << server_fd->StrError();

  auto device_config = cuttlefish::DeviceConfig::Get();
  if (!device_config) {
    LOG(ERROR) << "Failed to obtain device configuration";
    return -1;
  }

  // Server loop
  while (true) {
    auto conn = cuttlefish::SharedFD::Accept(*server_fd);
    LOG(INFO) << "Connection received on configuration server";

    bool succeeded = device_config->SendRawData(conn);
    if (succeeded) {
      LOG(INFO) << "Successfully sent device configuration";
    } else {
      LOG(ERROR) << "Failed to send the device configuration: "
                 << conn->StrError();
    }
  }
}
