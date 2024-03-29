LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COREBASE}/meta/COPYING.MIT;md5=3da9cfbcb788c80a0384361b4de20420"
PV = "1.0"

PACKAGE_ARCH = "${MACHINE_ARCH}"
inherit packagegroup

PACKAGES = "\
    ${PN} \
    ${PN}-base \
    ${PN}-debugger \
    ${PN}-filesystem \
    ${PN}-library \
    ${PN}-net \
"


RDEPENDS:${PN} = "\
    ${PN}-base \
    ${PN}-debugger \
    ${PN}-filesystem \
    ${PN}-library \
    ${PN}-net \
"

SUMMARY:${PN}-debugger = "Debugging tools"
RDEPENDS:${PN}-debugger = "\
    gdb \
    gdbserver \
    strace \
    usbutils \
    valgrind \
    libcap-bin \
"

SUMMARY:${PN}-base = "Base development tools"
RDEPENDS:${PN}-base = "\
    autoconf \
    automake \
    bc \
    binutils \
    binutils-symlinks \
    bison \
    ccache \
    cmake \
    cpp \
    cpp-symlinks \
    diffstat \
    diffutils \
    flex \
    g++ \
    g++-symlinks \
    gcc \
    gcc-symlinks \
    git \
    glibc-utils \
    gnu-config \
    imagemagick \
    intltool \
    libstdc++-dev \
    libtool \
    m4 \
    make \
    nasm \
    patch \
    pkgconfig \
    rpm-build \
    ${@bb.utils.contains('DISTRO_FEATURES', 'x11', 'twm', '', d)} \
    yasm \
"

SUMMARY:${PN}-filesystem = "File system tools"
RDEPENDS:${PN}-filesystem = "\
    cifs-utils \
    dosfstools \
    e2fsprogs \
    ecryptfs-utils \
    exfat-utils \
    f2fs-tools \
    fuse-exfat \
    gptfdisk \
    mtools \
    squashfs-tools \
"

SUMMARY:${PN}-library = "Extended libraries"
RDEPENDS:${PN}-library = "\
    ${@bb.utils.contains('TARGET_ARCH', 'x86_64', 'gmmlib-dev', '', d)} \
    ${@bb.utils.contains('TARGET_ARCH', 'x86_64', 'itt-dev', '', d)} \
    ${@bb.utils.contains('TARGET_ARCH', 'x86_64', 'itt-staticdev', '', d)} \
    libpcap \
    libsoup-2.4 \
    python3-attrs \
    python3-dbus \
    python3-numpy \
    python3-pip \
    python3-pyserial \
    python3-modules \
    python3-pip \
    python3-psutil \
    libgpiod-tools \
"

SUMMARY:${PN}-net = "Network Tools"
RDEPENDS:${PN}-net = "\
   connman \
   connman-client \
   connman-tools \
   dhcpcd \
   ethtool \
   iproute2 \
   openssh \
   rsync \
"
