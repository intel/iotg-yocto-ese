# this file makes the LTS kernel the default boot option
require conf/kernels/presets/lts-6.6.conf

# internal testing, uncommnet it when staging is ready
include ${TOPDIR}/conf/internal/kernel-2023-6.6.conf
