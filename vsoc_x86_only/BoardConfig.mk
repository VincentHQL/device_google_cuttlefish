#
# Copyright 2020 The Android Open-Source Project
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
# x86 (32-bit kernel) target for Cuttlefish
#

-include device/google/cuttlefish/shared/BoardConfig.mk

# GKI_VER is defined in kernel.mk, if not defined in the environment variable.
BOARD_KERNEL_MODULE_INTERFACE_VERSIONS := $(GKI_VER)-android12-0

TARGET_BOARD_PLATFORM := vsoc_x86
TARGET_ARCH := x86
TARGET_ARCH_VARIANT := x86
TARGET_CPU_ABI := x86

BOARD_VENDOR_RAMDISK_KERNEL_MODULES += $(wildcard device/google/cuttlefish_prebuilts/kernel/$(GKI_VER)-i686/*.ko)
