# Use /lib64 even if not multilib
require conf/multilib.conf
MULTILIBS = ""

# support virtualization
DISTRO_FEATURES_append = " virtualization"

# applies to all multiconfig

# available multiconfigs
# users may mask uneeded ones to speed up bitbake
BBMULTICONFIG ??= "x86 x86-ese-installer x86-rt x86-mlt x86-skylake x86-musl x86-minimal x86-2020-minimal x86-minimal-netboot x86-minimal-provisioning x86-qemu_host x86-2020 x86-rt-2020"

# Machine Selection
MACHINE ??= "intel-corei7-64"
# Take note that as we are building 3rd party ingredient.
# We need the LICENSE_FLAGS below.
LICENSE_FLAGS_WHITELIST += "commercial"

# enable gcc security flags and optimizations
require conf/distro/include/security_flags.inc
EXTRA_OECONF_BASE_append = " --enable-default-pie --enable-default-ssp --enable-host-shared"
EXTRA_OECONF_BASE_append_x86 = " --enable-cld --enable-cet"
EXTRA_OECONF_BASE_append_x86-64 = " --enable-cld --enable-cet"
EXTRA_OECONF_BASE_append_libc-glibc = " --enable-gnu-unique-object --enable-vtable-verify"
EXTRA_OECONF_append_x86-64_pn-glibc = " --enable-static-pie --enable-cet"
RUNTIMETARGET_append_pn-gcc-runtime_libc-glibc = " libvtv"
CONFIGUREOPTS_append_pn-musl = " --enable-optimize=size"

# Remove unneeded applciations
PACKAGECONFIG_remove_pn-alsa-tools = "echomixer envy24control rmedigicontrol"
PACKAGECONFIG_remove_pn-gstreamer1.0-plugins-good = "speex"
GSTEXAMPLES = ""
RDEPENDS_packagegroup-meta-oe-multimedia_remove = "yavta"
RDEPENDS_packagegroup-core-x11-utils_remove = "xinput-calibrator"
RDEPENDS_packagegroup-base-ext2_remove = "hdparm"
RDEPENDS_packagegroup-core-full-cmdline-extended_remove = "iputils"
RDEPENDS_packagegroup-core-x11-sato-base_remove = "matchbox-config-gtk settings-daemon"
RDEPENDS_packagegroup-core-x11-sato-apps_remove = "l3afpad"
RDEPENDS_packagegroup-base-serial_remove = "lrzsz"
RDEPENDS_packagegroup-core-tools-testapps_remove = "blktool lrzsz"
RDEPENDS_packagegroup-self-hosted-extended_remove = "lrzsz settings-daemon"
DEPENDS_remove_pn-perf = "libnewt"
MACHINE_FEATURES_remove_pn-matchbox-panel-2 = "acpi"
PACKAGECONFIG_remove_pn-iproute2 = "tipc"
PACKAGECONFIG_remove = "tcp-wrappers"
EXTRA_OECONF_remove_pn-matchbox-panel-2 = "--enable-startup-notification"
EXTRA_OECONF_append_pn-matchbox-panel-2 = " --disable-startup-notification"
DEPENDS_remove_pn-matchbox-panel-2 = "startup-notification"
EXTRA_OECONF_remove_pn-matchbox-desktop = "--enable-startup-notification"
EXTRA_OECONF_append_pn-matchbox-desktop = " --disable-startup-notification"
DEPENDS_remove_pn-matchbox-desktop = "startup-notification"
DEPENDS_remove_pn-matchbox-wm = "startup-notification"
EXTRA_OECONF_remove_pn-matchbox-wm = "--enable-startup-notification"
EXTRA_OECONF_append_pn-matchbox-wm = " --disable-startup-notification"
NETWORK_MANAGER = "connman"
FILEMANAGER = ""
PTEST_ENABLED_pn-util-linux = ""
PTEST_ENABLED_pn-openssh = ""
PACKAGECONFIG_remove_pn-vim = "gtkgui"
BAD_RECOMMENDATIONS_append = " rng-tools"
RRECOMMENDS_openssh-sshd_remove = "rng-tools"
PACKAGECONFIG_remove_pn-apparmor = "perl"

# fix grub-native vs grub-efi-native conflict
PREFERRED_PROVIDER_grub-efi-native = "grub-native"
PREFERRED_PROVIDER_grub-efi = "grub-efi"

# kernel 4.15 or later should not be using CRDA
# https://git.kernel.org/pub/scm/linux/kernel/git/mcgrof/crda.git/tree/README
RDEPENDS_packagegroup-base-wifi_remove = "wireless-regdb-static"
RDEPENDS_packagegroup-base-wifi_append = " wireless-regdb"

# OVMF Secureboot support
PACKAGECONFIG_append_pn-ovmf = " secureboot"

# EFI System Partition mountpoint
EFI_PREFIX = "/boot/efi"
EFIDIR = "/EFI/BOOT"

# mender does not use conf/image-uefi.conf
BBMASK_append = " meta-mender/meta-mender-core/recipes-bsp/(grub/grub-efi_%.bbappend|systemd/systemd-boot_%.bbappend)"
# meta-intel-edison nor meta-debian is not used
BBMASK_append = " meta-mender/meta-mender-core/recipes-bsp/u-boot/u-boot-fw-utils_%.bbappend"

# meta-intel-edison nor meta-debian is not used
BBMASK_append = " meta-mender/meta-mender-core/recipes-bsp/u-boot/u-boot-fw-utils_%.bbappend"

# serial console settings
SERIAL_CONSOLES_append = " 115200;ttyS4 115200;ttyS5"

# systemd should not be repackaged due to os-release timestamp update
# It is pulled in via RRECOMMENDS_${PN}
SIGGEN_EXCLUDE_SAFE_RECIPE_DEPS += "systemd->os-release"

# squashfs zstd tooling
PACKAGECONFIG_append_pn-squashfs-tools-native = " zstd"
