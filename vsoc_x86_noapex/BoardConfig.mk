#
# Copyright 2019 The Android Open-Source Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

#
# x86 target for Cuttlefish that doesn't support APEX.
#

include device/google/cuttlefish/vsoc_x86/BoardConfig.mk

TARGET_FLATTEN_APEX := true
BOARD_VENDOR_RAMDISK_KERNEL_MODULES += $(wildcard device/google/cuttlefish_kernel/5.4-x86_64/*.ko)
