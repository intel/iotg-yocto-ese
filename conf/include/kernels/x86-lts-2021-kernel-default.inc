# this file makes the LTS kernel the default boot option
require conf/kernels/presets/lts-5.15.conf

# internal testing
include ${TOPDIR}/conf/internal/kernel-2021-5.15.conf
