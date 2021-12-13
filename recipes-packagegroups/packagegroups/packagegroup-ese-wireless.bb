SUMMARY = "Packagegroup for wireless utilities."
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COREBASE}/meta/COPYING.MIT;md5=3da9cfbcb788c80a0384361b4de20420"
PV = "1.0"

PACKAGE_ARCH = "${MACHINE_ARCH}"
inherit packagegroup

PACKAGES = "${PN}"

SUMMARY:${PN} = "Wireless tools"
RDEPENDS:${PN} = "\
    bluez5 \
    bluez5-obex \
    busybox-udhcpc \
    ${@bb.utils.contains("DISTRO_FEATURES", "systemd", "busybox", "busybox-udhcpd", d)} \
    ofono \
    hostapd \
    wpa-supplicant \
    util-linux-rfkill \
"
