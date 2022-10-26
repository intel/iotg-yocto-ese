# Use /lib64 even if not multilib
require conf/multilib.conf
MULTILIBS = ""

# support virtualization
DISTRO_FEATURES:append = " virtualization"

# applies to all multiconfig

# available multiconfigs
# users may mask uneeded ones to speed up bitbake
BBMULTICONFIG ??= "x86 x86-ese-installer x86-rt x86-mlt x86-skylake x86-musl x86-minimal x86-minimal-netboot x86-minimal-provisioning \
  x86-2020-minimal x86-2020-minimal-netboot x86-2020 x86-rt-2020 \
  x86-2021 x86-2021-minimal x86-2021-minimal-netboot x86-rt-2021 x86-2021-qemu_host \
  x86-next x86-rt-next"

# Machine Selection
MACHINE ??= "intel-corei7-64"
# Take note that as we are building 3rd party ingredient.
# We need the LICENSE_FLAGS below.
LICENSE_FLAGS_ACCEPTED += "commercial"

# enable gcc security flags and optimizations
require conf/distro/include/security_flags.inc
EXTRA_OECONF_BASE:append = " --enable-default-pie --enable-default-ssp --enable-host-shared"
EXTRA_OECONF_BASE:append:x86 = " --enable-cld --enable-cet"
EXTRA_OECONF_BASE:append:x86-64 = " --enable-cld --enable-cet"
EXTRA_OECONF_BASE:append:libc-glibc = " --enable-gnu-unique-object --enable-vtable-verify"
EXTRA_OECONF:append:x86-64:pn-glibc = " --enable-static-pie --enable-cet"
RUNTIMETARGET:append:pn-gcc-runtime:libc-glibc = " libvtv"
CONFIGUREOPTS:append:pn-musl = " --enable-optimize=size"

# Remove unneeded applciations
PACKAGECONFIG:remove:pn-alsa-tools = "echomixer envy24control rmedigicontrol"
PACKAGECONFIG:remove:pn-gstreamer1.0-plugins-good = "speex"
GSTEXAMPLES = ""
RDEPENDS:packagegroup-meta-oe-multimedia:remove = "yavta"
RDEPENDS:packagegroup-core-x11-utils:remove = "xinput-calibrator"
RDEPENDS:packagegroup-base-ext2:remove = "hdparm"
RDEPENDS:packagegroup-core-full-cmdline-extended:remove = "iputils"
RDEPENDS:packagegroup-core-x11-sato-base:remove = "matchbox-config-gtk settings-daemon"
RDEPENDS:packagegroup-core-x11-sato-apps:remove = "l3afpad"
RDEPENDS:packagegroup-base-serial:remove = "lrzsz"
RDEPENDS:packagegroup-core-tools-testapps:remove = "blktool lrzsz"
RDEPENDS:packagegroup-self-hosted-extended:remove = "lrzsz settings-daemon"
DEPENDS:remove:pn-perf = "libnewt"
MACHINE_FEATURES:remove:pn-matchbox-panel-2 = "acpi"
PACKAGECONFIG:remove:pn-iproute2 = "tipc"
PACKAGECONFIG:remove = "tcp-wrappers"
EXTRA_OECONF:remove:pn-matchbox-panel-2 = "--enable-startup-notification"
EXTRA_OECONF:append:pn-matchbox-panel-2 = " --disable-startup-notification"
DEPENDS:remove:pn-matchbox-panel-2 = "startup-notification"
EXTRA_OECONF:remove:pn-matchbox-desktop = "--enable-startup-notification"
EXTRA_OECONF:append:pn-matchbox-desktop = " --disable-startup-notification"
DEPENDS:remove:pn-matchbox-desktop = "startup-notification"
DEPENDS:remove:pn-matchbox-wm = "startup-notification"
EXTRA_OECONF:remove:pn-matchbox-wm = "--enable-startup-notification"
EXTRA_OECONF:append:pn-matchbox-wm = " --disable-startup-notification"
NETWORK_MANAGER = "connman"
FILEMANAGER = ""
PTEST_ENABLED:pn-util-linux = ""
PTEST_ENABLED:pn-openssh = ""
PACKAGECONFIG:remove:pn-vim = "gtkgui"
BAD_RECOMMENDATIONS:append = " rng-tools"
RRECOMMENDS:openssh-sshd:remove = "rng-tools"
PACKAGECONFIG:remove:pn-apparmor = "perl"

# fix grub-native vs grub-efi-native conflict
PREFERRED_PROVIDER_grub-efi-native = "grub-native"
PREFERRED_PROVIDER_grub-efi = "grub-efi"

# kernel 4.15 or later should not be using CRDA
# https://git.kernel.org/pub/scm/linux/kernel/git/mcgrof/crda.git/tree/README
RDEPENDS:packagegroup-base-wifi:remove = "wireless-regdb-static"
RDEPENDS:packagegroup-base-wifi:append = " wireless-regdb"

# OVMF Secureboot support
PACKAGECONFIG:append:pn-ovmf = " secureboot"

# EFI System Partition mountpoint
EFI_PREFIX = "/boot/efi"
EFIDIR = "/EFI/BOOT"

# mender does not use conf/image-uefi.conf
BBMASK:append = " meta-mender/meta-mender-core/recipes-bsp/(grub/grub-efi_%.bbappend|systemd/systemd-boot_%.bbappend)"
# meta-intel-edison nor meta-debian is not used
BBMASK:append = " meta-mender/meta-mender-core/recipes-bsp/u-boot/u-boot-fw-utils_%.bbappend"

# Fix parsing error of meta-mender-core/recipes-bsp/grub/grub-efi-mender-precompiled_2.04.bb
# Variable 'MENDER_EFI_LOADER' is defined in bbclass file 'mender-setup-grub.inc' but 'INHERIT:remove = "mender-setup"'
# removing the inclusion of bbclass file 'mender-setup-grub.inc'
MENDER_EFI_LOADER:pn-grub-efi-mender-precompiled ??= ""

# meta-intel-edison nor meta-debian is not used
BBMASK:append = " meta-mender/meta-mender-core/recipes-bsp/u-boot/u-boot-fw-utils_%.bbappend"

# serial console settings
SERIAL_CONSOLES:append = " 115200;ttyS4 115200;ttyS5"

# systemd should not be repackaged due to os-release timestamp update
# It is pulled in via RRECOMMENDS:${PN}
SIGGEN_EXCLUDE_SAFE_RECIPE_DEPS += "systemd->os-release"

# squashfs zstd tooling
PACKAGECONFIG:append:pn-squashfs-tools-native = " zstd"

# meta virtualization is outdated
BBMASK:append = " meta-virtualization/recipes-core/busybox/"
