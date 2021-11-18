### Set this to secure-boot-certificates to use randomly generated keys, preset keys will not be used
# the same randomly generated keys will be used until secure-boot-certificates yocto recipe is cleaned up
# use "bitbake [multiconfing prefix]secure-boot-certificates -c cleansstate" to clean up
# pregenerated certs/keys will only be used if set to "secure-boot-certificates-pregenerated"
# set to "secure-boot-certificates" to use randomly generated keys
PREFERRED_PROVIDER_virtual/secure-boot-certificates = "secure-boot-certificates"
# these lines configure openssl automatic key generation options
SECURE_BOOT_CERT_GEN_ALGO = "rsa"
SECURE_BOOT_CERT_GEN_LENGTH = "4096"
SECURE_BOOT_CERT_GEN_HASH = "sha512"
SECURE_BOOT_CERT_GEN_SUBJECT = "/CN=BSP Signing Key/"

### Pregenerated secure boot Certs/Keys for secure-boot-certificates-pregenerated
# these have no effect on automatic key generation
PREGENERATED_SIGNING_KEY_TYPE = "sha256"
PREGENERATED_SIGNING_KEY_DIR  = "${TOPDIR}/cert/${PREGENERATED_SIGNING_KEY_TYPE}"
PREGENERATED_SIGNING_KEY_PK_KEY = "PK.key"
PREGENERATED_SIGNING_KEY_PK_CRT = "PK.crt"
PREGENERATED_SIGNING_KEY_KEK_KEY = "KEK.key"
PREGENERATED_SIGNING_KEY_KEK_CRT = "KEK.crt"
PREGENERATED_SIGNING_KEY_DB_KEY = "DB.key"
PREGENERATED_SIGNING_KEY_DB_CRT = "DB.crt"
PREGENERATED_SIGNING_KEY_MOK_KEY = "yocto.key"
PREGENERATED_SIGNING_KEY_MOK_CRT = "yocto.crt"
PREGENERATED_SIGNING_KEY_SHIM_KEY = "shim.key"
PREGENERATED_SIGNING_KEY_SHIM_CRT = "shim.crt"
### End Pregenerated Keys

### slimboot settings
# SBLIMAGE_AUTH: auth type, used to generate container, "" allows the GenContainer script to determine the appropriate value.
#                Other possibilities are RSA2048_PSS_SHA2_256 and RSA3072_PSS_SHA2_384
# SBLIMAGE_BOOT_DEFAULT_CONTAINER - container name used by loader firmware
# SBLIMAGE_BOOT_SUPPORTS_SOFTLINK - whether to use symlinks or not to save space, the older loader firmware does not support symlinks
SBLIMAGE_AUTH = ""
SBLIMAGE_CERT_GEN_ALGO = "rsa"
SBLIMAGE_BOOT_CERT_GEN_LENGTH = "3072"
SBLIMAGE_BOOT_CERT_GEN_HASH = "sha384"
SBLIMAGE_BOOT_DEFAULT_CONTAINER = "sbl_os"
SBLIMAGE_BOOT_SUPPORTS_SOFTLINK = "1"

SBLIMAGE_BOOT_CERT_GEN_SUBJECT = "/CN=BSP Signing Key/"
PREFERRED_PROVIDER_virtual/secure-boot-certificates-slimboot = "secure-boot-certificates-slimboot"

### Pregenerated secure boot Certs/Keys for Slimboot
# Uncomment these lines to use pregenerated keys
#PREFERRED_PROVIDER_virtual/secure-boot-certificates-slimboot = "secure-boot-certificates-slimboot-pregenerated"
#PREGENERATED_SIGNING_KEY_SLIMBOOT_KEY = "${TOPDIR}/cert/TestSigningPrivateKey.pem"

# Enable efitools LockDown.efi
# this program allows inserting keys into setup mode secure boot
IMAGE_FEATURES[validitems] += "efi-lockdown"
IMAGE_FEATURES_append = " efi-lockdown"
MENDER_GRUBCONF_CHAINLOADER[efi-secure-boot-lockdown] = "$prefix/LockDown${GNU_EFI_ARCH}.efi"

# user overrides
include ${TOPDIR}/conf/multiconfig/signing.inc
include ${TOPDIR}/conf/signing.inc

# internal stubs
include ${TOPDIR}/conf/internal/signing.inc
