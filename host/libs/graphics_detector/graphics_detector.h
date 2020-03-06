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
#pragma once

#include <string>

namespace cuttlefish {

struct GraphicsAvailability {
  bool has_gl = false;
  bool has_gles1 = false;
  bool has_gles2 = false;
  bool has_egl = false;
  bool has_egl_default_display = false;
  std::string egl_client_extensions;
  std::string egl_version;
  std::string egl_vendor;
  std::string egl_extensions;
  bool has_egl_surfaceless_with_gles = false;
  bool has_vulkan = false;
  bool has_discrete_gpu = false;
  std::string discrete_gpu_device_name;
  std::string discrete_gpu_device_extensions;
};

GraphicsAvailability GetGraphicsAvailability();

std::string GetGraphicsAvailabilityString(const GraphicsAvailability& info);

}  // namespace cuttlefish