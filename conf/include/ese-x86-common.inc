#
# This file is your local configuration file and is where all local user settings
# are placed. The comments in this file give some guide to the options a new user
# to the system might want to change but pretty much any configuration option can
# be set in this file. More adventurous users can look at local.conf.extended
# which contains other examples of configuration which can be placed in this file
# but new users likely won't need any of them initially.
#
# Lines starting with the '#' character are commented out and in some cases the
# default values are provided as comments to show people example syntax. Enabling
# the option is a question of removing the # character and making any change to the
# variable as required.

# Security package
IMAGE_INSTALL_append = " libseccomp apparmor jhi smack"
DISTRO_FEATURES_append = " apparmor"

# Apparmor & seccomp support
APPEND += "apparmor=1 security=apparmor mem_sleep_default=deep"
DEPENDS_append_pn-systemd = " apparmor"
PACKAGECONFIG_append_pn-systemd = " gnutls seccomp lz4"
PACKAGECONFIG_append_pn-gnutls = " seccomp"
BBCLASSEXTEND_pn-libseccomp = "native nativesdk"

# early preinit-env handler
IMAGE_INSTALL_append = " preinit-env"
APPEND_append = " init=/sbin/preinit-env"

# Network package
IMAGE_INSTALL_append = " mosquitto"

PREFERRED_VERSION_systemd-bootchart = "233%"

# Runtime environment export setting for x11
IMAGE_INSTALL_append = " xserver-nodm-config"

BSP_SUBTYPE = "x86"

MACHINE_FEATURES_remove = "pcbios"

DISTRO_FEATURES_append = " x11 wayland vulkan"
CORE_IMAGE_EXTRA_INSTALL += "wayland weston"
DISTRO_FEATURES_NATIVE_append = " x11"
DISTRO_FEATURES_NATIVESDK_append = " x11"

# Set features for media
IMAGE_INSTALL_append = " gstreamer1.0-libav"
DISTRO_FEATURES_append = " msdk onevpl"
IMAGE_INSTALL_append = " intel-media-driver"
IMAGE_INSTALL_append = "${@bb.utils.contains("DISTRO_FEATURES","msdk", " intel-mediasdk", "", d)}"
IMAGE_INSTALL_append = "${@bb.utils.contains("DISTRO_FEATURES","msdk", " intel-mediasdk-samples", "", d)}"
IMAGE_INSTALL_append = "${@bb.utils.contains("DISTRO_FEATURES","onevpl", " onevpl onevpl-intel-gpu", "", d)}"
PACKAGECONFIG_append_pn-gstreamer1.0-libav = " libav"
PACKAGECONFIG_append_pn-gstreamer1.0-plugins-base = "${@bb.utils.filter('DISTRO_FEATURES', 'opengl', d)}"
IMAGE_INSTALL_append = " vulkan-loader"

# mesa iris driver
PACKAGECONFIG_append_pn-mesa_class-target = " gallium gallium-llvm"
MESA_FORCE_DRIVER = "iris"
PREFERRED_PROVIDER_virtual/mesa-native = "${PREFERRED_PROVIDER_virtual/mesa}-native"
PACKAGECONFIG_append_pn-mesa-native_class-native = " gles"
# clang/llvm native build is broken, mesa doing the insane by using native llvm to find out about host llvm
# make sure some PACKAGECONFIG is at least common in meta-clang clang/llvm
PACKAGECONFIG_append_pn-clang = " rtti eh  shared-libs"
PACKAGECONFIG_append_pn-clang-native = " rtti eh shared-libs"
DISTRO_FEATURES_append = " dri3"

# Add fwupdate packages
IMAGE_INSTALL_append = " fwupdate fwupdate-boot"

# Remove ltp to reduce image size
PACKAGE_EXCLUDE = "ltp"
RDEPENDS_packagegroup-core-tools-testapps_remove = " ltp"

# Required additional host tools
HOSTTOOLS += "git-lfs"

# Enable ocl-icd and neo for elkhart-lake
IMAGE_INSTALL_append = " ocl-icd intel-compute-runtime"

# Enable ptp daemons
# temporary disable gptp IMAGE_INSTALL_append = " gptp linuxptp net-snmp"
IMAGE_INSTALL_append = " linuxptp net-snmp"

# Enable cups
IMAGE_INSTALL_append = " cups"

# Enable freeglut for elkhart-lake
IMAGE_INSTALL_append = " freeglut"

#################
# ESE PACKAGES
#################

# ESE specific packagegroups
IMAGE_INSTALL_append = " packagegroup-ese-coretools"
IMAGE_INSTALL_append = " packagegroup-ese-graphics"
IMAGE_INSTALL_append = " packagegroup-ese-graphics-2d"
IMAGE_INSTALL_append = " packagegroup-ese-graphics-display"
IMAGE_INSTALL_append = " packagegroup-ese-graphics-media"
IMAGE_INSTALL_append = " packagegroup-ese-graphics-tools"
IMAGE_INSTALL_append = " packagegroup-ese-multimedia"
IMAGE_INSTALL_append = " packagegroup-ese-wireless"
IMAGE_INSTALL_append = " packagegroup-core-x11-extended"

# Weston/Wayland
IMAGE_INSTALL_append = " wayland weston"
PACKAGECONFIG_append_pn-weston = " headless"

# Contents from meta-tpm2 and configuration
IMAGE_INSTALL_append = " packagegroup-ese-tpm2"
EXTRA_OECONF_append_pn-tpm2-tss = " --with-tctidefaultmodule=libtss2-tcti-tabrmd.so"

# Add multimedia components
DISTRO_FEATURES_append = " pulseaudio"

# linux-firmware
IMAGE_INSTALL_append = " linux-firmware"


# Bluetooth management
IMAGE_INSTALL_append = " bluez5-noinst-tools bluez5-testtools"

# Enable TPM drivers
MACHINE_FEATURES_append = " tpm"

# Enable LMS
IMAGE_INSTALL_append = " lms"

# Logging support
IMAGE_INSTALL_append = " logrotate"

# Remove unnecessary packages installed in sato image
IMAGE_INSTALL_remove = " packagegroup-core-x11-sato-games kernel-devsrc"

# Remove unnecessary image features added in sato-sdk image
IMAGE_FEATURES_remove = "eclipse-debug tools-profile"

# X11-related
IMAGE_INSTALL_append = " xinput"

# Production-type image optional
#INHERIT += "extrausers"
#EXTRA_USERS_PARAMS = "${@bb.utils.contains("IMAGE_FEATURES","allow-empty-password", "", "usermod -P 1876*18 root;", d)}"

# Install TSN tool
IMAGE_INSTALL_append = " ethtool iproute2 iproute2-tc iperf3 tcpdump linuxptp stress-ng"

# Enable live555
IMAGE_INSTALL_append = " live555-examples"

# Qemu virtualization support
DISTRO_FEATURES_append = " virtualization"
IMAGE_INSTALL_append = " qemu ovmf-edk2"
PACKAGECONFIG_append_pn-qemu = " libusb glx gtk+"
# Set preferred version for qemu
# Limiting the preffered version to hardknott only since it is causing warning issues on dunfell
PREFERRED_VERSION_qemu ?= "${@bb.utils.contains("LAYERSERIES_COMPAT_core","hardknott", "6.0%", "", d)}"
PREFERRED_VERSION_qemu-native ?= "${@bb.utils.contains("LAYERSERIES_COMPAT_core","hardknott", "6.0%", "", d)}"
PREFERRED_VERSION_qemu-system-native ?= "${@bb.utils.contains("LAYERSERIES_COMPAT_core","hardknott", "6.0%", "", d)}"
PREFERRED_VERSION_nativesdk-qemu ?= "${@bb.utils.contains("LAYERSERIES_COMPAT_core","hardknott", "6.0%", "", d)}"

# Using icewm instead of matchbox
IMAGE_INSTALL_append = " icewm"
RDEPENDS_packagegroup-core-x11-base_remove_pn-packagegroup-core-x11-base = "matchbox-terminal matchbox-wm mini-x-session"
RDEPENDS_packagegroup-core-x11-sato-base_remove_pn-packagegroup-core-x11-sato = " \
    matchbox-desktop \
    matchbox-session-sato \
    matchbox-keyboard \
    matchbox-keyboard-applet \
    matchbox-keyboard-im \
    matchbox-config-gtk \
    xcursor-transparent-theme \
    adwaita-icon-theme \
    settings-daemon \
    shutdown-desktop \
"
RDEPENDS_packagegroup-core-x11-sato_remove_pn-packagegroup-core-x11-sato = "packagegroup-core-x11-sato-games packagegroup-core-x11-sato-apps"

#################
# ESE PACKAGES
#################

# use openssh instead of dropbear
IMAGE_FEATURES_remove = "ssh-server-dropbear"
IMAGE_FEATURES_append = " ssh-server-openssh"

# Workaround for the bug to generate nativesdk
TOOLCHAIN_HOST_TASK_append = " nativesdk-cmake-dev"

# Workaround kernel 4.20 no longer having oldnoconfig
KERNEL_CONFIG_COMMAND = "oe_runmake_call -C ${S} O=${B} olddefconfig"

#skip apparmor ptest
PTEST_ENABLED_pn-apparmor = ""
SYSTEMD_AUTO_ENABLE_pn-apparmor = "enable"

# Enable secureboot for elkhart-lake
require ./ese-signing-defaults.inc
SECURITY_NO_FORTIFY_CFLAGS = "-fstack-protector-strong -pie -fpie -Wformat -Wformat-security"
SECUREBOOT = "true"

# Grub-efi provider
EFI_PROVIDER = "grub-efi"
# Shim will load this file
SHIM_LOADER_IMAGE = "grubx64.efi"

# efi boot manager
IMAGE_INSTALL_append = " efibootmgr"

# enable signed kernel image for secure boot
# uncomment to bundle Intel CPU microcode update with kernel
#KERNEL_CLASSES_append = " kernel-microcode"
# uncomment to bundle Intel i915 firmware into the kernel
#KERNEL_CLASSES_append = " kernel-i915-fw"
# enable slimboot
# bundle initrd for secure boot (kernel signing is now handled by ese-image-features post-processing)
# slimboot IMAGE_FEATURES to install slimboot kernel subpackages
KERNEL_CLASSES_append = " kernel-initrd"
IMAGE_FEATURES_append = " slimboot"

# default kernel (virtual provider set in multiconfig with internal overrides)
IMAGE_INSTALL_append = " kernel-image kernel-modules"

#Add usb_modeswitch support
IMAGE_INSTALL_append = " usb-modeswitch"

# convenience packge to pull in any other out-of-tree kernel drivers
# See KERNEL_PROVIDERS_EXTRA_MODULES variable
IMAGE_INSTALL_append = " packagegroup-kernel-oot"

# DPDK
IMAGE_INSTALL_append = " dpdk dpdk-staticdev dpdk-dev dpdk-examples dpdk-tools"
PACKAGECONFIG_append_pn-dpdk = " afxdp libvirt"
KERNEL_PROVIDERS_EXTRA_MODULES[5.4] += "dpdk-module dpdk-kmods"
KERNEL_PROVIDERS_EXTRA_MODULES[5.10] += "dpdk-module dpdk-kmods"

# wifi module is handled specially so that it may be possible to have some kernels using the out of tree module and others
# using the internal module, see meta-intel-ese-bsp/classes/kernel-wifi-conf.bbclass
# enabling the driver from backport-iwlwifi disables the kernel in-tree version
DISTRO_FEATURES_append = " backport-iwlwifi-5.4 backport-iwlwifi-5.10"
KERNEL_PROVIDERS_EXTRA_MODULES_WIFI_COMPAT ?= ""
KERNEL_PROVIDERS_EXTRA_MODULES_WIFI_COMPAT_append = "${@bb.utils.contains("DISTRO_FEATURES", "backport-iwlwifi-5.4",  " 5.4",  "", d)}"
KERNEL_PROVIDERS_EXTRA_MODULES_WIFI_COMPAT_append = "${@bb.utils.contains("DISTRO_FEATURES", "backport-iwlwifi-5.10", " 5.10", "", d)}"
KERNEL_PROVIDERS_EXTRA_MODULES[5.4]  += "${@bb.utils.contains("DISTRO_FEATURES", "backport-iwlwifi-5.4",  "backport-iwlwifi", "", d)}"
KERNEL_PROVIDERS_EXTRA_MODULES[5.10] += "${@bb.utils.contains("DISTRO_FEATURES", "backport-iwlwifi-5.10", "backport-iwlwifi", "", d)}"

# autoload modules
KERNEL_MODULE_AUTOLOAD_append = " configfs uhid"

# subregion capsule generation tool
IMAGE_INSTALL_append = " fbu"

# Additional serial consoles
APPEND_append = " console=ttyS4,115200n8 console=ttyS5,115200n8 i915.force_probe=*" 

# OS-release info
IMAGE_INSTALL_append = " os-release"

# IASImage settings for Slimboot
IMAGE_INSTALL_append = " kernel-image-sblimage"

## Enable Smack support ##
#OVERRIDES .= ":smack"
DISTRO_FEATURES_append = " smack"

# Remove initscripts from the image altogether.
VIRTUAL-RUNTIME_initscripts = ""

# Smack utilities is useful.
#CORE_IMAGE_EXTRA_INSTALL += " systemd-analyze coreutils smack-userspace"

# Exclude conflicting smack recipe
#BBMASK = "meta-security/recipes-mac/smack"

## End of Smack support ##


###################
# OpenVINO PACKAGES
###################

# Enable clDNN only when needed, as this will pull in additional compile-time
# and runtime dependencies for Intel Graphics Compute Runtime for OpenCL
PACKAGECONFIG_append_pn-openvino-inference-engine = " opencl"

# Enable building inference engine python API.
PACKAGECONFIG_append_pn-openvino-inference-engine = " python3"

# This adds inference engine related libraries to the target image
IMAGE_INSTALL_append = " openvino-inference-engine"

# This adds inference engine samples to the target image
IMAGE_INSTALL_append = " openvino-inference-engine-samples"

# Include inference engine python API package to the target image.
# This is required for running e2e_oss test cases
IMAGE_INSTALL_append = " openvino-inference-engine-python3"

# Enable MYRIAD plugin
IMAGE_INSTALL_append = " openvino-inference-engine-vpu-firmware"

# Include model optimizer to the target image.
# This is required for running e2e_oss test cases
IMAGE_INSTALL_append = " openvino-model-optimizer"

# python3 packages needed by the inference engine python test script to transform the input image to expected format
IMAGE_INSTALL_append = " python3-opencv python3-numpy"

# Set preferred version for TBB
PREFERRED_VERSION_tbb = "2021.2%"

# Include optimized deep learning models and a set of demos
IMAGE_INSTALL_append = " open-model-zoo"

########## clang/llvm size problems
BAD_RECOMMENDATIONS_append = " clang-staticdev"

# Adding recipes for platform specific changes
IMAGE_INSTALL_append = " audio-hda-load"

# usb mouse wakeup and SATA PM and GBE and Serial PM
IMAGE_INSTALL_append = " udev-usbpower udev-satapower udev-gbepower udev-serialpower"

# tccsdk dependencies
IMAGE_INSTALL_append = "${@bb.utils.contains("IMAGE_FEATURES", "dev-pkgs", " itt-staticdev", "", d)}"

# Enable tpm2-abrmd service
SYSTEMD_AUTO_ENABLE_pn-tpm2-abrmd = "enable"

# user overrides
include ${TOPDIR}/conf/multiconfig/x86-common.inc

# internal stubs
include ${TOPDIR}/conf/internal/ese-x86-common-mc-${BB_CURRENT_MC}.inc

# Kernel parameters for dma-buf module to increase the size of buffer list.
# The default size of dma-buf list are limited and it can't support large frame size
# which require dma-buf support.
APPEND_append = " udmabuf.list_limit=8192"
