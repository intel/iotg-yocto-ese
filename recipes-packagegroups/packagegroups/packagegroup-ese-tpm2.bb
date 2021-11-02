SUMMARY = "Packagegroup for TPM2 TCG TSS userspace and utilities."
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COREBASE}/meta/COPYING.MIT;md5=3da9cfbcb788c80a0384361b4de20420"
PV = "1.0"

PACKAGE_ARCH = "${MACHINE_ARCH}"
inherit packagegroup

PACKAGES = "\
    ${PN} \
    ${PN}-tss \
"

SUMMARY:${PN} = "tpm2 all components"
RDEPENDS:${PN} = "\
    tpm2-abrmd \
    tpm2-tools \
    ${PN}-tss \
"

SUMMARY:${PN}-tss = "tpm2 tss packages"
RDEPENDS:${PN}-tss = "\
    libtss2-mu \
    libtss2-mu-dev \
    libtss2-mu-staticdev \
    libtss2-tcti-device \
    libtss2-tcti-device-dev \
    libtss2-tcti-device-staticdev \
    libtss2-tcti-mssim \
    libtss2-tcti-mssim-dev \
    libtss2-tcti-mssim-staticdev \
    libtss2 \
    libtss2-dev \
    libtss2-staticdev \
    tpm2-tss \
"
