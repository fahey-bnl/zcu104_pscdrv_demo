#!../../bin/linux-x86_64/myioc

#- SPDX-FileCopyrightText: 2005 Argonne National Laboratory
#-
#- SPDX-License-Identifier: EPICS

#- You may have to change myioc to something else
#- everywhere it appears in this file

#< envPaths

## Register all support components
dbLoadDatabase "../../dbd/myioc.dbd"
myioc_registerRecordDeviceDriver(pdbbase) 

createPSC("dev1", "192.168.1.10", 7, 0)
setPSCSendBlockSize("dev1", 0, 8)
setPSCSendBlockSize("dev1", 4, 8)

createPSC("dev2", "192.168.1.10", 600, 1)

## Load record instances
dbLoadRecords("../../db/myioc.db","user=link,ONAME=dev1,INAME=dev2,P=debug:")

iocInit()

## Start any sequence programs
#seq sncmyioc,"user=link"
