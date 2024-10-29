SUMMARY = "Essential codec, encoder, decoder for audio and video"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COREBASE}/meta/COPYING.MIT;md5=3da9cfbcb788c80a0384361b4de20420"
PV = "1.0"
PR = "r1"

PACKAGE_ARCH = "${MACHINE_ARCH}"
inherit packagegroup

PACKAGES = "${PN} ${PN}-audio-base ${PN}-audio-codecs ${PN}-audio-libraries \
            ${PN}-video-codecs ${PN}-media-player"

RDEPENDS:${PN} = "\
    ${PN}-audio-base \
    ${PN}-audio-codecs \
    ${PN}-audio-libraries \
    ${PN}-video-codecs \
    ${PN}-media-player \
"

SUMMARY:${PN}-audio-base = "Essential Audio Support"
PULSEAUDIO_PKGS ?= "\
    pulseaudio-server \
    pulseaudio-misc \
    pulseaudio-init \
    pulseaudio-module-bluetooth-discover \
    pulseaudio-module-bluetooth-policy \
    pulseaudio-module-bluez5-device \
    pulseaudio-module-bluez5-discover \
"
RDEPENDS:${PN}-audio-base = "\
    libasound \
    alsa-tools \
    alsa-utils \
    ${@bb.utils.contains('DISTRO_FEATURES', 'pulseaudio', '${PULSEAUDIO_PKGS}', '', d)} \
"

SUMMARY:${PN}-audio-codecs = "Audio Codecs Support"
RDEPENDS:${PN}-audio-codecs = "\
    flac \
"

SUMMARY:${PN}-audio-libraries = "Audio Libraries Support"
RDEPENDS:${PN}-audio-libraries = "\
    alsa-lib \
"

SUMMARY:${PN}-video-codecs = "Video Codecs Support"
RDEPENDS:${PN}-video-codecs = "\
    x264 \
"

SUMMARY:${PN}-media-player = "Media Player Support"
RDEPENDS:${PN}-media-player = "\
"
