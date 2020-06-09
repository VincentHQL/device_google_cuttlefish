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

$(call inherit-product, device/google/cuttlefish/shared/auto/device.mk)
$(call inherit-product, device/google/cuttlefish/vsoc_x86_64/kernel.mk)

PRODUCT_NAME := aosp_cf_x86_auto
PRODUCT_DEVICE := vsoc_x86
PRODUCT_MANUFACTURER := Google
PRODUCT_MODEL := Cuttlefish x86 auto
PRODUCT_PACKAGE_OVERLAYS += device/google/cuttlefish/vsoc_x86/auto/overlay


# Whitelisted packages per user type
PRODUCT_COPY_FILES += \
    device/google/cuttlefish/vsoc_x86/auto/preinstalled-packages-product-car-cuttlefish.xml:$(TARGET_COPY_OUT_PRODUCT)/etc/sysconfig/preinstalled-packages-product-car-cuttlefish.xml
