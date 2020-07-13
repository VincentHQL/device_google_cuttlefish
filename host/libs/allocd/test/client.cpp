/*
 * Copyright (C) 2020 The Android Open Source Project
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

#include <android-base/logging.h>
#include <gflags/gflags.h>
#include <json/json.h>
#include <unistd.h>

#include <iostream>

#include "common/libs/fs/shared_fd.h"
#include "host/libs/allocd/request.h"
#include "host/libs/allocd/utils.h"
#include "host/libs/config/logging.h"

using namespace cuttlefish;

DEFINE_string(socket_path, kDefaultLocation, "Socket path");
DEFINE_bool(id, false, "Request new UUID");
DEFINE_bool(ifcreate, false, "Request a new Interface");
DEFINE_string(ifdestroy, "", "Request an interface be destroyed");
DEFINE_bool(shutdown, false, "Shutdown Resource Allocation Server");

int main(int argc, char* argv[]) {
  cuttlefish::DefaultSubprocessLogging(argv);
  google::ParseCommandLineFlags(&argc, &argv, true);

  SharedFD monitor_socket = cuttlefish::SharedFD::SocketLocalClient(
      FLAGS_socket_path, false, SOCK_STREAM);
  if (!monitor_socket->IsOpen()) {
    // LOG(ERROR) << "Unable to connect to launcher monitor at " << monitor_path
    LOG(ERROR) << "Unable to connect to launcher monitor on "
               << FLAGS_socket_path << ": " << monitor_socket->StrError();
    return 1;
  }

  if (FLAGS_id) {
    Json::Value req;
    req["request_type"] = "allocate_id";
    SendJsonMsg(monitor_socket, req);

    auto resp_opt = RecvJsonMsg(monitor_socket);
    if (!resp_opt.has_value()) {
      std::cout << "Bad Response from server\n";
      return -1;
    }

    auto resp = resp_opt.value();
    std::cout << resp << "\n";
    std::cout << "New ID operation: " << resp["request_status"] << std::endl;
    std::cout << "New ID: " << resp["id"] << std::endl;
  }

  if (FLAGS_ifcreate) {
    Json::Value req;
    req["request_type"] = "create_interface";
    req["uid"] = geteuid();
    req["iface_type"] = "mtap";
    SendJsonMsg(monitor_socket, req);

    auto resp_opt = RecvJsonMsg(monitor_socket);
    if (!resp_opt.has_value()) {
      std::cout << "Bad Response from server\n";
      return -1;
    }

    auto resp = resp_opt.value();

    std::cout << resp << "\n";
    std::cout << "Create Interface operation: " << resp["request_status"]
              << std::endl;
    std::cout << resp["iface_name"] << std::endl;
  }

  if (!FLAGS_ifdestroy.empty()) {
    Json::Value req;
    req["request_type"] = "destroy_interface";
    req["iface_name"] = FLAGS_ifdestroy;
    SendJsonMsg(monitor_socket, req);

    LOG(INFO) << "Request Interface : '" << FLAGS_ifdestroy << "' be removed";

    auto resp_opt = RecvJsonMsg(monitor_socket);
    if (!resp_opt.has_value()) {
      std::cout << "Bad Response from server\n";
      return -1;
    }

    auto resp = resp_opt.value();

    std::cout << resp << "\n";

    std::cout << "Destroy Interface operation: " << resp["request_status"]
              << std::endl;
    std::cout << resp["iface_name"] << std::endl;
  }

  if (FLAGS_shutdown) {
    Json::Value req;
    req["request_type"] = "shutdown";

    cuttlefish::SendJsonMsg(monitor_socket, req);

    auto resp_opt = cuttlefish::RecvJsonMsg(monitor_socket);
    if (!resp_opt.has_value()) {
      std::cout << "Bad Response from server\n";
      return -1;
    }

    auto resp = resp_opt.value();

    std::cout << "Shutdown operation: " << resp["request_status"] << std::endl;
  }

  return 0;
}
