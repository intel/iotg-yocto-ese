SUMMARY = "Basic utilities and library"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COREBASE}/meta/COPYING.MIT;md5=3da9cfbcb788c80a0384361b4de20420"
PV = "1.0"

PACKAGE_ARCH = "${MACHINE_ARCH}"
inherit packagegroup

PACKAGES = "\
    ${PN} \
    ${PN}-base \
    ${PN}-filesystem \
    ${PN}-library \
"

RDEPENDS:${PN} = "\
    ${PN}-base \
    ${PN}-filesystem \
    ${PN}-library \
"

SUMMARY:${PN}-base = "Basic utilities"
RDEPENDS:${PN}-base = "\
    bash \
    coreutils \
    dnf \
    file \
    gawk \
    gettext \
    less \
    nano \
    ncurses \
    nspr \
    pciutils \
    procps \
    python3 \
    rpm \
    screen \
    tzdata \
    udev \
    util-linux \
    util-linux-getopt \
    util-linux-blkid \
    util-linux-lscpu \
    vim \
    wget \
    openssl-bin \
    debianutils \
    ${@bb.utils.contains('DISTRO_FEATURES', 'x11','xterm', '', d)} \
"

SUMMARY:${PN}-filesystem = "Filesystem, archive and compression tools"
RDEPENDS:${PN}-filesystem = "\
    bzip2 \
    gzip \
    tar \
    unzip \
    xz \
"

SUMMARY:${PN}-library = "Core libraries"
RDEPENDS:${PN}-library = "\
    glibc \
    gtk+3 \
    libstdc++ \
    zlib \
"
