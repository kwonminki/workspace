#
_XDCBUILDCOUNT = 0
ifneq (,$(findstring path,$(_USEXDCENV_)))
override XDCPATH = C:/ti/bios_6_76_02_02/packages;C:/ti/bios_6_76_02_02/packages/myBoard;C:/ti/dsplib_c674x_3_4_0_0/packages;C:/Users/olleh/workspace_v9/exam2/.config
override XDCROOT = C:/ti/ccs901/xdctools_3_55_00_11_core
override XDCBUILDCFG = ./config.bld
endif
ifneq (,$(findstring args,$(_USEXDCENV_)))
override XDCARGS = 
override XDCTARGETS = 
endif
#
ifeq (0,1)
PKGPATH = C:/ti/bios_6_76_02_02/packages;C:/ti/bios_6_76_02_02/packages/myBoard;C:/ti/dsplib_c674x_3_4_0_0/packages;C:/Users/olleh/workspace_v9/exam2/.config;C:/ti/ccs901/xdctools_3_55_00_11_core/packages;..
HOSTOS = Windows
endif
