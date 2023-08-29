# this file makes the LTS kernel the default boot option
require conf/kernels/presets/lts-6.1.conf

# internal testing, uncommnet it when staging is ready
include ${TOPDIR}/conf/internal/kernel-2022-6.1.conf