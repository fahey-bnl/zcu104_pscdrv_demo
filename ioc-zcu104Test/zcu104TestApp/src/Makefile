# SPDX-FileCopyrightText: 2003 Argonne National Laboratory
#
# SPDX-License-Identifier: EPICS

TOP=../..

include $(TOP)/configure/CONFIG
#----------------------------------------
#  ADD MACRO DEFINITIONS AFTER THIS LINE
#=============================

#=============================
# Build the IOC application

PROD_IOC = zcu104Test
# zcu104Test.dbd will be created and installed
DBD += zcu104Test.dbd

# zcu104Test.dbd will be made up from these files:
zcu104Test_DBD += base.dbd
zcu104Test_DBD += pscCore.dbd

# Include dbd files from all support applications:
#zcu104Test_DBD += xxx.dbd

# Add all the support libraries needed by this IOC
#zcu104Test_LIBS += xxx

# zcu104Test_registerRecordDeviceDriver.cpp derives from zcu104Test.dbd
zcu104Test_SRCS += zcu104Test_registerRecordDeviceDriver.cpp

# Build the main IOC entry point on workstation OSs.
zcu104Test_SRCS_DEFAULT += zcu104TestMain.cpp
zcu104Test_SRCS_vxWorks += -nil-

# Add support from base/src/vxWorks if needed
#zcu104Test_OBJS_vxWorks += $(EPICS_BASE_BIN)/vxComLibrary

# Finally link to the EPICS Base libraries
ifneq (YES,$(USE_FFTW))
zcu104Test_DBD += pscSig.dbd
zcu104Test_LIBS += pscSig
endif

ifneq (YES,$(USE_UDPFAST))
zcu104Test_DBD += pscSig.dbd
zcu104Test_LIBS += pscSig
endif

zcu104Test_LIBS += pscCore
zcu104Test_LIBS += $(EPICS_BASE_IOC_LIBS)

zcu104Test_SYS_LIBS += event_core event_extra
zcu104Test_SYS_LIBS_Linux += event_pthreads

#===========================

include $(TOP)/configure/RULES
#----------------------------------------
#  ADD RULES AFTER THIS LINE

