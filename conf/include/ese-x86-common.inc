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

#zlib providers
# Only use the Intel-tuned zlib for target builds to improve reuse
PREFERRED_PROVIDER_zlib = "zlib-intel"
PREFERRED_PROVIDER_zlib-native = "zlib-native"
PREFERRED_PROVIDER_nativesdk-zlib = "nativesdk-zlib"

# Security package
IMAGE_INSTALL:append = " libseccomp apparmor jhi smack"
DISTRO_FEATURES:append = " seccomp security apparmor"

# Apparmor & seccomp support
APPEND += "apparmor=1 security=apparmor mem_sleep_default=deep"
DEPENDS:append:pn-systemd = " apparmor"
PACKAGECONFIG:append:pn-systemd = " gnutls seccomp lz4"
PACKAGECONFIG:append:pn-gnutls = " seccomp"
BBCLASSEXTEND:pn-libseccomp = "native nativesdk"

# early preinit-env handler
IMAGE_INSTALL:append = " preinit-env"
APPEND:append = " init=/sbin/preinit-env"

# Network package
IMAGE_INSTALL:append = " mosquitto"

PREFERRED_VERSION_systemd-bootchart = "233%"

# Runtime environment export setting for x11
IMAGE_INSTALL:append = " xserver-nodm-config"

BSP_SUBTYPE = "x86"

MACHINE_FEATURES:remove = "pcbios"

DISTRO_FEATURES:append = " x11 wayland vulkan"
CORE_IMAGE_EXTRA_INSTALL += "wayland weston"
DISTRO_FEATURES_NATIVE:append = " x11"
DISTRO_FEATURES_NATIVESDK:append = " x11"

# Set features for media
IMAGE_INSTALL:append = " gstreamer1.0-libav"
DISTRO_FEATURES:append = " msdk onevpl"
IMAGE_INSTALL:append = " intel-media-driver"
IMAGE_INSTALL:append = "${@bb.utils.contains("DISTRO_FEATURES","msdk", " intel-mediasdk", "", d)}"
IMAGE_INSTALL:append = "${@bb.utils.contains("DISTRO_FEATURES","msdk", " intel-mediasdk-samples", "", d)}"
IMAGE_INSTALL:append = "${@bb.utils.contains("DISTRO_FEATURES","onevpl", " onevpl onevpl-intel-gpu", "", d)}"
PACKAGECONFIG:append:pn-gstreamer1.0-libav = " libav"
PACKAGECONFIG:append:pn-gstreamer1.0-plugins-base = "${@bb.utils.filter('DISTRO_FEATURES', 'opengl', d)}"
IMAGE_INSTALL:append = " vulkan-loader"

# mesa iris driver
PACKAGECONFIG:append:pn-mesa:class-target = " gallium gallium-llvm"
MESA_FORCE_DRIVER = "iris"
PREFERRED_PROVIDER_virtual/mesa-native = "${PREFERRED_PROVIDER_virtual/mesa}-native"
PACKAGECONFIG:append:pn-mesa-native:class-native = " gles"
# clang/llvm native build is broken, mesa doing the insane by using native llvm to find out about host llvm
# make sure some PACKAGECONFIG is at least common in meta-clang clang/llvm
## Dunfell clang10 is bugged, causing llvm/clang constructors to run twice if tools depending on it is built with
## shared clang/llvm runtime libraries
##
## We still want the compiler to be dynamically linked on the runtime image if possible due to image size concerns
## reference: https://reviews.llvm.org/file/data/5mlinpbqf726tpeke5xr/PHID-FILE-xmzquxeysicqtqdiuyxi/file
PACKAGECONFIG:append:pn-clang = " rtti eh  shared-libs"
PACKAGECONFIG:append:pn-clang-native = " rtti eh"
# prefer consistency where possible
PACKAGECONFIG:append:pn-clang-native = "${@bb.utils.contains("LAYERSERIES_COMPAT_core","dunfell", "", " shared-libs", d)}"

DISTRO_FEATURES:append = " dri3"

# Add fwupdate packages
IMAGE_INSTALL:append = " fwupdate fwupdate-boot"

# Remove ltp to reduce image size
PACKAGE_EXCLUDE = "ltp"
RDEPENDS:packagegroup-core-tools-testapps:remove = " ltp"

# Required additional host tools
HOSTTOOLS += "git-lfs"

# Enable ocl-icd and neo for elkhart-lake
IMAGE_INSTALL:append = " ocl-icd intel-compute-runtime"

# Enable ptp daemons
# temporary disable gptp IMAGE_INSTALL:append = " gptp linuxptp net-snmp"
IMAGE_INSTALL:append = " linuxptp net-snmp"

# Enable cups
IMAGE_INSTALL:append = " cups"

# Enable freeglut for elkhart-lake
IMAGE_INSTALL:append = " freeglut"

#################
# ESE PACKAGES
#################

# ESE specific packagegroups
IMAGE_INSTALL:append = " packagegroup-ese-coretools"
IMAGE_INSTALL:append = " packagegroup-ese-graphics"
IMAGE_INSTALL:append = " packagegroup-ese-graphics-2d"
IMAGE_INSTALL:append = " packagegroup-ese-graphics-display"
IMAGE_INSTALL:append = " packagegroup-ese-graphics-media"
IMAGE_INSTALL:append = " packagegroup-ese-graphics-tools"
IMAGE_INSTALL:append = " packagegroup-ese-multimedia"
IMAGE_INSTALL:append = " packagegroup-ese-wireless"
IMAGE_INSTALL:append = " packagegroup-core-x11-extended"

# Weston/Wayland
IMAGE_INSTALL:append = " wayland weston"
PACKAGECONFIG:append:pn-weston = " headless"

# Contents from meta-tpm2 and configuration
IMAGE_INSTALL:append = " packagegroup-ese-tpm2"
EXTRA_OECONF:append:pn-tpm2-tss = " --with-tctidefaultmodule=libtss2-tcti-tabrmd.so"

# Add multimedia components
DISTRO_FEATURES:append = " pulseaudio"

# linux-firmware
IMAGE_INSTALL:append = " linux-firmware intel-linux-firmware"


# Bluetooth management
IMAGE_INSTALL:append = " bluez5-noinst-tools bluez5-testtools"

# Enable TPM drivers
MACHINE_FEATURES:append = " tpm"

# Enable LMS
IMAGE_INSTALL:append = " lms"

# Logging support
IMAGE_INSTALL:append = " logrotate"

# Remove unnecessary packages installed in sato image
IMAGE_INSTALL:remove = " packagegroup-core-x11-sato-games kernel-devsrc"

# Remove unnecessary image features added in sato-sdk image
IMAGE_FEATURES:remove = "eclipse-debug tools-profile"

# X11-related
IMAGE_INSTALL:append = " xinput"

# Production-type image optional
#INHERIT += "extrausers"
#EXTRA_USERS_PARAMS = "${@bb.utils.contains("IMAGE_FEATURES","allow-empty-password", "", "usermod -P 1876*18 root;", d)}"

# Install TSN tool
IMAGE_INSTALL:append = " ethtool iproute2 iproute2-tc iperf3 tcpdump linuxptp stress-ng"

# Enable live555
IMAGE_INSTALL:append = " live555-examples"

# Qemu virtualization support
DISTRO_FEATURES:append = " virtualization"
IMAGE_INSTALL:append = " qemu ovmf-edk2"
PACKAGECONFIG:append:pn-qemu = " libusb glx gtk+"
# Set preferred version for qemu
# Limiting the preffered version to hardknott only since it is causing warning issues on dunfell
PREFERRED_VERSION_qemu ?= "${@bb.utils.contains("LAYERSERIES_COMPAT_core","hardknott", "6.0%", "", d)}"
PREFERRED_VERSION_qemu-native ?= "${@bb.utils.contains("LAYERSERIES_COMPAT_core","hardknott", "6.0%", "", d)}"
PREFERRED_VERSION_qemu-system-native ?= "${@bb.utils.contains("LAYERSERIES_COMPAT_core","hardknott", "6.0%", "", d)}"
PREFERRED_VERSION_nativesdk-qemu ?= "${@bb.utils.contains("LAYERSERIES_COMPAT_core","hardknott", "6.0%", "", d)}"

# Using icewm instead of matchbox
IMAGE_INSTALL:append = " icewm"
RDEPENDS:packagegroup-core-x11-base:remove:pn-packagegroup-core-x11-base = "matchbox-terminal matchbox-wm mini-x-session"
RDEPENDS:packagegroup-core-x11-sato-base:remove:pn-packagegroup-core-x11-sato = " \
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
RDEPENDS:packagegroup-core-x11-sato:remove:pn-packagegroup-core-x11-sato = "packagegroup-core-x11-sato-games packagegroup-core-x11-sato-apps"

#################
# ESE PACKAGES
#################

# use openssh instead of dropbear
IMAGE_FEATURES:remove = "ssh-server-dropbear"
IMAGE_FEATURES:append = " ssh-server-openssh"

# Workaround for the bug to generate nativesdk
TOOLCHAIN_HOST_TASK:append = " nativesdk-cmake-dev"

# Workaround kernel 4.20 no longer having oldnoconfig
KERNEL_CONFIG_COMMAND = "oe_runmake_call -C ${S} O=${B} olddefconfig"

#skip apparmor ptest
PTEST_ENABLED:pn-apparmor = ""
SYSTEMD_AUTO_ENABLE:pn-apparmor = "enable"

# Enable secureboot for elkhart-lake
require ./ese-signing-defaults.inc
SECURITY_NO_FORTIFY_CFLAGS = "-fstack-protector-strong -pie -fpie -Wformat -Wformat-security"
SECUREBOOT = "true"

# Grub-efi provider
EFI_PROVIDER = "grub-efi"
# Shim will load this file
SHIM_LOADER_IMAGE = "grubx64.efi"

# efi boot manager
IMAGE_INSTALL:append = " efibootmgr"

# enable signed kernel image for secure boot
# uncomment to bundle Intel CPU microcode update with kernel
#KERNEL_CLASSES:append = " kernel-microcode"
# uncomment to bundle Intel i915 firmware into the kernel
#KERNEL_CLASSES:append = " kernel-i915-fw"
# enable slimboot
# bundle initrd for secure boot (kernel signing is now handled by ese-image-features post-processing)
# slimboot IMAGE_FEATURES to install slimboot kernel subpackages
KERNEL_CLASSES:append = " kernel-initrd"
IMAGE_FEATURES:append = " slimboot"

# default kernel (virtual provider set in multiconfig with internal overrides)
IMAGE_INSTALL:append = " kernel-image kernel-modules"

#Add usb_modeswitch support
IMAGE_INSTALL:append = " usb-modeswitch"

# convenience packge to pull in any other out-of-tree kernel drivers
# See KERNEL_PROVIDERS_EXTRA_MODULES variable
IMAGE_INSTALL:append = " packagegroup-kernel-oot"

# DPDK
IMAGE_INSTALL:append = " dpdk dpdk-staticdev dpdk-dev dpdk-examples dpdk-tools"
PACKAGECONFIG:append:pn-dpdk = " afxdp libvirt"
KERNEL_PROVIDERS_EXTRA_MODULES[5.4] += "dpdk-module dpdk-kmods"
KERNEL_PROVIDERS_EXTRA_MODULES[5.10] += "dpdk-module dpdk-kmods"
KERNEL_PROVIDERS_EXTRA_MODULES[5.15] += "dpdk-module dpdk-kmods"

# wifi module is handled specially so that it may be possible to have some kernels using the out of tree module and others
# using the internal module, see meta-intel-ese-bsp/classes/kernel-wifi-conf.bbclass
# enabling the driver from backport-iwlwifi disables the kernel in-tree version
DISTRO_FEATURES:append = " backport-iwlwifi-5.4 backport-iwlwifi-5.10 backport-iwlwifi-5.15"
KERNEL_PROVIDERS_EXTRA_MODULES_WIFI_COMPAT ?= ""
KERNEL_PROVIDERS_EXTRA_MODULES_WIFI_COMPAT:append = "${@bb.utils.contains("DISTRO_FEATURES", "backport-iwlwifi-5.4",  " 5.4",  "", d)}"
KERNEL_PROVIDERS_EXTRA_MODULES_WIFI_COMPAT:append = "${@bb.utils.contains("DISTRO_FEATURES", "backport-iwlwifi-5.10", " 5.10", "", d)}"
KERNEL_PROVIDERS_EXTRA_MODULES_WIFI_COMPAT:append = "${@bb.utils.contains("DISTRO_FEATURES", "backport-iwlwifi-5.15", " 5.15", "", d)}"
KERNEL_PROVIDERS_EXTRA_MODULES[5.4]  += "${@bb.utils.contains("DISTRO_FEATURES", "backport-iwlwifi-5.4",  "backport-iwlwifi", "", d)}"
KERNEL_PROVIDERS_EXTRA_MODULES[5.10] += "${@bb.utils.contains("DISTRO_FEATURES", "backport-iwlwifi-5.10", "backport-iwlwifi", "", d)}"
KERNEL_PROVIDERS_EXTRA_MODULES[5.15] += "${@bb.utils.contains("DISTRO_FEATURES", "backport-iwlwifi-5.15", "backport-iwlwifi", "", d)}"

# autoload modules
KERNEL_MODULE_AUTOLOAD:append = " configfs uhid"

# subregion capsule generation tool
IMAGE_INSTALL:append = " fbu"

# Additional serial consoles
APPEND:append = " console=ttyS4,115200n8 console=ttyS5,115200n8 i915.force_probe=*" 

# OS-release info
IMAGE_INSTALL:append = " os-release"

# IASImage settings for Slimboot
IMAGE_INSTALL:append = " kernel-image-sblimage"

## Enable Smack support ##
#OVERRIDES .= ":smack"
DISTRO_FEATURES:append = " smack"

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
PACKAGECONFIG:append:pn-openvino-inference-engine = " opencl"

# Enable building inference engine python API.
PACKAGECONFIG:append:pn-openvino-inference-engine = " python3"

# This adds inference engine related libraries to the target image
IMAGE_INSTALL:append = " openvino-inference-engine"

# This adds inference engine samples to the target image
IMAGE_INSTALL:append = " openvino-inference-engine-samples"

# Include inference engine python API package to the target image.
# This is required for running e2e_oss test cases
IMAGE_INSTALL:append = " openvino-inference-engine-python3"

# Enable MYRIAD plugin
IMAGE_INSTALL:append = " openvino-inference-engine-vpu-firmware"

# Include model optimizer to the target image.
# This is required for running e2e_oss test cases
IMAGE_INSTALL:append = " openvino-model-optimizer"

# python3 packages needed by the inference engine python test script to transform the input image to expected format
IMAGE_INSTALL:append = " python3-opencv python3-numpy"

# Set preferred version for TBB
PREFERRED_VERSION_tbb = "2021.2%"

# Include optimized deep learning models and a set of demos
IMAGE_INSTALL:append = " open-model-zoo"

########## clang/llvm size problems
BAD_RECOMMENDATIONS:append = " clang-staticdev"

# Adding recipes for platform specific changes
IMAGE_INSTALL:append = " audio-hda-load"

# usb mouse wakeup and SATA PM and GBE and Serial PM
IMAGE_INSTALL:append = " udev-usbpower udev-satapower udev-gbepower udev-serialpower"

# tccsdk dependencies
IMAGE_INSTALL:append = "${@bb.utils.contains("IMAGE_FEATURES", "dev-pkgs", " itt-staticdev", "", d)}"

# Enable tpm2-abrmd service
SYSTEMD_AUTO_ENABLE:pn-tpm2-abrmd = "enable"

# user overrides
include ${TOPDIR}/conf/multiconfig/x86-common.inc

# internal stubs
include ${TOPDIR}/conf/internal/ese-x86-common-mc-${BB_CURRENT_MC}.inc

# Kernel parameters for dma-buf module to increase the size of buffer list.
# The default size of dma-buf list are limited and it can't support large frame size
# which require dma-buf support.
APPEND:append = " udmabuf.list_limit=8192"
