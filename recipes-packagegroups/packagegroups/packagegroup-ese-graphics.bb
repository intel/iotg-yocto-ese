SUMMARY = "Graphics support for display, 2D, 3D and media"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COREBASE}/meta/COPYING.MIT;md5=3da9cfbcb788c80a0384361b4de20420"
PV = "1.0"
PR = "r1"

PACKAGE_ARCH = "${MACHINE_ARCH}"
inherit packagegroup

PACKAGES = "\
    ${PN} \
    ${PN}-base \
    ${PN}-2d \
    ${PN}-3d \
    ${PN}-display \
    ${PN}-media \
    ${PN}-tools \
"

SUMMARY:${PN} = "Graphics Packagegroup"
RDEPENDS:${PN} = "\
    ${PN}-base \
    ${PN}-2d \
    ${PN}-3d \
    ${PN}-display \
    ${PN}-media \
    ${PN}-tools \
"

SUMMARY:${PN}-base = "Graphics Base Support"
RDEPENDS:${PN}-base = "\
    gstreamer1.0 \
    ${@bb.utils.contains('DISTRO_FEATURES', 'x11', 'gstreamer1.0-plugins-bad', '', d)} \
    gstreamer1.0-plugins-base \
    gstreamer1.0-plugins-good \
    gstreamer1.0-rtsp-server \
    libdrm \
    metrics-discovery \
"

SUMMARY:${PN}-2d = "2D Graphics Support"
RDEPENDS:${PN}-2d = "\
    cairo \
    dmidecode \
    ${@bb.utils.contains('DISTRO_FEATURES', 'x11','xf86-video-intel', '', d)} \
"

# piglit moved to meta-intel-ese-extra-pre
SUMMARY:${PN}-3d = "3D Graphics Support"
RDEPENDS:${PN}-3d = "\
    glew \
    ${@bb.utils.contains('DISTRO_FEATURES', 'x11','libglu', '', d)} \
    mesa \
"

SUMMARY:${PN}-display = "Graphics Display Support"
RDEPENDS:${PN}-display = "\
    libjpeg-turbo \
    libpng \
"

SUMMARY:${PN}-media = "Graphics Media Support"
RDEPENDS:${PN}-media = "\
    libva \
    libva-utils \
    ${@bb.utils.contains('DISTRO_FEATURES', 'x11','gstreamer1.0-vaapi', '', d)} \
    v4l-utils \
"

SUMMARY:${PN}-tools = "Graphics Tools Support"
RDEPENDS:${PN}-tools = "\
    fontconfig \
    freetype \
    glog \
    gtk+3 \
    numactl \
    pango \
"
