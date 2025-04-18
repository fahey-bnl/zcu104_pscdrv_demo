#!../../bin/linux-x86_64/zcu104Test

#- SPDX-FileCopyrightText: 2005 Argonne National Laboratory
#-
#- SPDX-License-Identifier: EPICS

#- You may have to change zcu104Test to something else
#- everywhere it appears in this file

#< envPaths

## Register all support components
dbLoadDatabase "../../dbd/zcu104Test.dbd"
zcu104Test_registerRecordDeviceDriver(pdbbase) 

## Load dev1: device input @ 192.168.1.10:7 with receive timeout turned off
createPSC("dev1", "192.168.1.10", 7, 0)
setPSCSendBlockSize("dev1", 4, 8)
setPSCSendBlockSize("dev1", 5, 8)

## Load dev2: device output @ 192.168.1.10:600 with receive timeout turned on
createPSC("dev2", "192.168.1.10", 600, 1)

## Load record instances
dbLoadRecords("../../db/myioc.db","ONAME=dev1,INAME=dev2,P=debug:")

iocInit()
