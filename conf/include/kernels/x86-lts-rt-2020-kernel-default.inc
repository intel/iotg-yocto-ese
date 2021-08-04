# this file makes the LTS kernel the default boot option
require conf/kernels/presets/lts-rt-5.10.conf

# internal testing
include ${TOPDIR}/conf/internal/kernel-2020-5.10.conf
