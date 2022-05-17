SUMMARY = "Dummy Package"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COREBASE}/meta/COPYING.MIT;md5=3da9cfbcb788c80a0384361b4de20420"
PV = "1.0"

# libsrtp gets rpm renamed to libsrtp2
PACKAGE_ARCH = "${TUNE_PKGARCH}"
inherit packagegroup
ALLOW_EMPTY:${PN} = "1"
