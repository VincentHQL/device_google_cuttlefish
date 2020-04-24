#
# Copyright (C) 2019 The Android Open Source Project
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
# All components inherited here go to system image (same as GSI system)
#
$(call inherit-product, $(SRC_TARGET_DIR)/product/mainline_system.mk)

PRODUCT_ENFORCE_ARTIFACT_PATH_REQUIREMENTS := relaxed

# TODO(ycchen): The component below will be in Q mainline, and will be removed
# from the whitelist when Q is released. See b/131162245 for some details.
PRODUCT_ARTIFACT_PATH_REQUIREMENT_WHITELIST += \
    system/apex/com.android.apex.cts.shim.apex \
    system/app/messaging/messaging.apk \
    system/lib/libframesequence.so \
    system/lib/libgiftranscode.so \

#
# All components inherited here go to product image (same as GSI product)
#
$(call inherit-product, device/google/cuttlefish/shared/phone/aosp_product.mk)

#
# All components inherited here go to vendor image
#
$(call inherit-product, device/google/cuttlefish/shared/phone/device_vendor.mk)

#
# Special settings for the target
#
DEVICE_PACKAGE_OVERLAYS += device/google/cuttlefish/vsoc_x86/phone/overlay

$(call inherit-product, device/google/cuttlefish/vsoc_x86/device.mk)


PRODUCT_NAME := aosp_cf_x86_pasan
PRODUCT_DEVICE := vsoc_x86
PRODUCT_MODEL := Cuttlefish x86 phone
