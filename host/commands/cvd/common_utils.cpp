/*
 * Copyright (C) 2022 The Android Open Source Project
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

#include "host/commands/cvd/common_utils.h"

#include <memory>
#include <sstream>

#include <android-base/file.h>
#include <android-base/logging.h>

#include "common/libs/utils/contains.h"
#include "common/libs/utils/files.h"
#include "host/commands/cvd/client.h"

namespace cuttlefish {

cvd::Request MakeRequest(const MakeRequestParam& args_and_envs,
                         cvd::WaitBehavior wait_behavior) {
  const auto& args = args_and_envs.cmd_args;
  const auto& env = args_and_envs.env;
  const auto& selector_args = args_and_envs.selector_args;
  cvd::Request request;
  auto command_request = request.mutable_command_request();
  for (const std::string& arg : args) {
    command_request->add_args(arg);
  }
  auto selector_opts = command_request->mutable_selector_opts();
  for (const std::string& selector_arg : selector_args) {
    selector_opts->add_args(selector_arg);
  }

  for (const auto& [key, value] : env) {
    (*command_request->mutable_env())[key] = value;
  }

  /*
   * the client must set the kAndroidHostOut environment variable. There were,
   * however, a few branches where kAndroidSoongHostOut replaced
   * kAndroidHostOut. Cvd server eventually read kAndroidHostOut only and set
   * both for the subtools.
   *
   * If none of the two are set, cvd server tries to use the parent directory of
   * the client cvd executable as env[kAndroidHostOut].
   *
   */
  if (!Contains(command_request->env(), kAndroidHostOut)) {
    const std::string new_android_host_out =
        Contains(command_request->env(), kAndroidSoongHostOut)
            ? (*command_request->mutable_env())[kAndroidSoongHostOut]
            : android::base::Dirname(android::base::GetExecutableDirectory());
    (*command_request->mutable_env())[kAndroidHostOut] = new_android_host_out;
  }

  std::unique_ptr<char, void (*)(void*)> cwd(getcwd(nullptr, 0), &free);
  command_request->set_working_directory(cwd.get());
  command_request->set_wait_behavior(wait_behavior);

  return request;
}

}  // namespace cuttlefish
