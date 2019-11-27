LOCAL_PATH := $(call my-dir)

cvd_host_package_tar := $(HOST_OUT)/cvd-host_package.tar.gz

.PHONY: hosttar
hosttar: $(cvd_host_package_tar)

# Build this by default when a developer types make
droidcore: $(cvd_host_package_tar)

# Build and store them on the build server.
$(call dist-for-goals, dist_files, $(cvd_host_package_tar))

bin_path := $(notdir $(HOST_OUT_EXECUTABLES))
lib_path := $(notdir $(HOST_OUT_SHARED_LIBRARIES))
tests_path := $(notdir $(HOST_OUT_NATIVE_TESTS))

cvd_host_executables := \
    adb \
    adbshell \
    launch_cvd \
    lpmake \
    lpunpack \
    socket_vsock_proxy \
    adb_connector \
    stop_cvd \
    vnc_server \
    cf_qemu.sh \
    cf_bpttool \
    virtual_usb_manager \
    kernel_log_monitor \
    extract-vmlinux \
    crosvm \
    aarch64-linux-gnu/crosvm \
    aarch64-linux-gnu/libepoxy.so.0 \
    aarch64-linux-gnu/libgbm.so.1 \
    aarch64-linux-gnu/libminijail.so \
    aarch64-linux-gnu/libvirglrenderer.so.0 \
    x86_64-linux-gnu/crosvm \
    x86_64-linux-gnu/libepoxy.so.0 \
    x86_64-linux-gnu/libgbm.so.1 \
    x86_64-linux-gnu/libminijail.so \
    x86_64-linux-gnu/libvirglrenderer.so.0 \
    logcat_receiver \
    config_server \
    tombstone_receiver \
    console_forwarder \
    assemble_cvd \
    run_cvd \
    cvd_status \

cvd_host_tests := \
    cuttlefish_thread_test \
    monotonic_time_test \
    cuttlefish_net_tests \

cvd_host_shared_libraries := \
    libbase.so \
    libcuttlefish_fs.so \
    libcuttlefish_utils.so \
    cuttlefish_tcp_socket.so \
    cuttlefish_net.so \
    liblog.so \
    libnl.so \
    libc++.so \
    liblp.so \
    libsparse-host.so \
    libcrypto-host.so \
    libcrypto_utils.so \
    libext4_utils.so \
    libz-host.so \
    libicuuc-host.so \
    libicui18n-host.so \
    libandroidicu-host.so \
    libcuttlefish_device_config.so \
    cdisk_spec.so \
    libprotobuf-cpp-full.so \
    libziparchive.so \


cvd_host_package_files := \
     $(addprefix $(bin_path)/,$(cvd_host_executables)) \
     $(addprefix $(lib_path)/,$(cvd_host_shared_libraries)) \
     $(foreach test,$(cvd_host_tests), ${tests_path}/$(test)/$(test)) \

$(cvd_host_package_tar): PRIVATE_FILES := $(cvd_host_package_files)
$(cvd_host_package_tar): $(addprefix $(HOST_OUT)/,$(cvd_host_package_files))
	$(hide) rm -rf $@ && tar Scfz $@.tmp -C $(HOST_OUT) $(PRIVATE_FILES)
	$(hide) mv $@.tmp $@
