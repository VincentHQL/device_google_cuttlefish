#
# Copyright (C) 2017 The Android Open Source Project
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

$(call inherit-product, device/google/cuttlefish/shared/tv/device.mk)
$(call inherit-product, device/google/cuttlefish/vsoc_x86/device.mk)

PRODUCT_NAME := aosp_cf_x86_tv
PRODUCT_DEVICE := vsoc_x86
PRODUCT_MANUFACTURER := Google
PRODUCT_MODEL := Cuttlefish x86 tv
# PRODUCT_PACKAGE_OVERLAYS := device/google/cuttlefish/vsoc_x86/tv/overlay
