SUMMARY = "X11 extended libraries and utilities"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COREBASE}/meta/COPYING.MIT;md5=3da9cfbcb788c80a0384361b4de20420"
PV = "1.0"
PR = "r1"

PACKAGE_ARCH = "${MACHINE_ARCH}"
inherit packagegroup

REQUIRED_DISTRO_FEATURES = "x11"

PACKAGES = "\
    ${PN} \
    ${PN}-utils \
"

SUMMARY_${PN} = "Extended X11 Libraries"
RDEPENDS_${PN} = "\
    packagegroup-core-x11-base \
    packagegroup-core-x11-extended-utils \
    libpciaccess \
    libx11 \
    libxaw7 \
    libxcb \
    libxcomposite \
    libxcursor \
    libxdamage \
    libxext \
    libxfixes \
    libxfont \
    libxft \
    libxi \
    libxinerama \
    libxkbcommon \
    libxkbfile \
    libxpm \
    libxrandr \
    libxrender \
    libxscrnsaver \
    libxshmfence \
    libxslt \
    libxt \
    libxv \
    libxvmc \
"

SUMMARY_${PN}-utils = "Extended X11 Utilities"
RDEPENDS_${PN}-utils = "\
    x11perf \
    xcb-util \
    xrdb \
    xserver-xorg \
"
