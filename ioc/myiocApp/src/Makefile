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

PROD_IOC = myioc
# myioc.dbd will be created and installed
DBD += myioc.dbd

# myioc.dbd will be made up from these files:
myioc_DBD += base.dbd
myioc_DBD += pscCore.dbd

# Include dbd files from all support applications:
#myioc_DBD += xxx.dbd

# Add all the support libraries needed by this IOC
#myioc_LIBS += xxx

# myioc_registerRecordDeviceDriver.cpp derives from myioc.dbd
myioc_SRCS += myioc_registerRecordDeviceDriver.cpp

# Build the main IOC entry point on workstation OSs.
myioc_SRCS_DEFAULT += myiocMain.cpp
myioc_SRCS_vxWorks += -nil-

# Add support from base/src/vxWorks if needed
#myioc_OBJS_vxWorks += $(EPICS_BASE_BIN)/vxComLibrary

# Finally link to the EPICS Base libraries
ifneq (YES,$(USE_FFTW))
myioc_DBD += pscSig.dbd
myioc_LIBS += pscSig
endif

ifneq (YES,$(USE_UDPFAST))
myioc_DBD += pscSig.dbd
myioc_LIBS += pscSig
endif

myioc_LIBS += pscCore
myioc_LIBS += $(EPICS_BASE_IOC_LIBS)

myioc_SYS_LIBS += event_core event_extra
myioc_SYS_LIBS_Linux += event_pthreads

#===========================

include $(TOP)/configure/RULES
#----------------------------------------
#  ADD RULES AFTER THIS LINE

