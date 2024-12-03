#include "sysmon_chp.h"

#define SYSMON_DEVICE_ID XPAR_XSYSMONPSU_0_DEVICE_ID

static XSysMonPsu SysMonInst;
u32 TempRawData;

void sysmon_init(){
    XSysMonPsu *SysMonInstPtr = &SysMonInst;
    XSysMonPsu_Config *ConfigPtr;

    ConfigPtr = XSysMonPsu_LookupConfig(SYSMON_DEVICE_ID);
    XSysMonPsu_CfgInitialize(SysMonInstPtr, ConfigPtr, ConfigPtr->BaseAddress);
    XSysMonPsu_SelfTest(SysMonInstPtr);

    //Settings for PS Side
    XSysMonPsu_SetSequencerMode(SysMonInstPtr, XSM_SEQ_MODE_SAFE, XSYSMON_PS);
    XSysMonPsu_SetAlarmEnables(SysMonInstPtr, 0x0, XSYSMON_PS);
    XSysMonPsu_SetAvg(SysMonInstPtr, XSM_AVG_16_SAMPLES, XSYSMON_PS);
    XSysMonPsu_SetSeqAvgEnables(SysMonInstPtr, XSYSMONPSU_SEQ_CH0_TEMP_MASK |
			XSYSMONPSU_SEQ_CH0_SUP1_MASK |
			XSYSMONPSU_SEQ_CH0_SUP2_MASK |
			XSYSMONPSU_SEQ_CH0_SUP3_MASK |
            XSYSMONPSU_SEQ_CH0_SUP4_MASK |
            XSYSMONPSU_SEQ_CH0_SUP5_MASK |
            XSYSMONPSU_SEQ_CH0_SUP6_MASK |
            XSYSMONPSU_SEQ_CH0_VP_VN_MASK |
            XSYSMONPSU_SEQ_CH0_VREFP_MASK |
            XSYSMONPSU_SEQ_CH0_VREFN_MASK |
            XSYSMONPSU_SEQ_CH2_SUP7_MASK |
            XSYSMONPSU_SEQ_CH2_SUP8_MASK |
            XSYSMONPSU_SEQ_CH2_SUP9_MASK |
            XSYSMONPSU_SEQ_CH2_SUP10_MASK |
			XSYSMONPSU_SEQ_CH0_CALIBRTN_MASK, XSYSMON_PS);
    XSysMonPsu_SetSeqChEnables(SysMonInstPtr, XSYSMONPSU_SEQ_CH0_TEMP_MASK |
			XSYSMONPSU_SEQ_CH0_SUP1_MASK |
			XSYSMONPSU_SEQ_CH0_SUP2_MASK |
			XSYSMONPSU_SEQ_CH0_SUP3_MASK |
            XSYSMONPSU_SEQ_CH0_SUP4_MASK |
            XSYSMONPSU_SEQ_CH0_SUP5_MASK |
            XSYSMONPSU_SEQ_CH0_SUP6_MASK |
            XSYSMONPSU_SEQ_CH0_VP_VN_MASK |
            XSYSMONPSU_SEQ_CH0_VREFP_MASK |
            XSYSMONPSU_SEQ_CH0_VREFN_MASK |
            XSYSMONPSU_SEQ_CH2_SUP7_MASK |
            XSYSMONPSU_SEQ_CH2_SUP8_MASK |
            XSYSMONPSU_SEQ_CH2_SUP9_MASK |
            XSYSMONPSU_SEQ_CH2_SUP10_MASK |
			XSYSMONPSU_SEQ_CH0_CALIBRTN_MASK, XSYSMON_PS);
    
    //Settings for PL Side
    XSysMonPsu_SetSequencerMode(SysMonInstPtr, XSM_SEQ_MODE_SAFE, XSYSMON_PL);
    XSysMonPsu_SetAlarmEnables(SysMonInstPtr, 0x0, XSYSMON_PL);
    XSysMonPsu_SetAvg(SysMonInstPtr, XSM_AVG_16_SAMPLES, XSYSMON_PL);
    XSysMonPsu_SetSeqAvgEnables(SysMonInstPtr, XSYSMONPSU_SEQ_CH0_TEMP_MASK |
			XSYSMONPSU_SEQ_CH0_SUP1_MASK |
			XSYSMONPSU_SEQ_CH0_SUP2_MASK |
			XSYSMONPSU_SEQ_CH0_SUP3_MASK |
            XSYSMONPSU_SEQ_CH0_SUP4_MASK |
            XSYSMONPSU_SEQ_CH0_SUP5_MASK |
            XSYSMONPSU_SEQ_CH0_SUP6_MASK |
            XSYSMONPSU_SEQ_CH0_VP_VN_MASK |
            XSYSMONPSU_SEQ_CH0_VREFP_MASK |
            XSYSMONPSU_SEQ_CH0_VREFN_MASK |
            XSYSMONPSU_SEQ_CH2_SUP7_MASK |
            XSYSMONPSU_SEQ_CH2_SUP8_MASK |
            XSYSMONPSU_SEQ_CH2_SUP9_MASK |
            XSYSMONPSU_SEQ_CH2_SUP10_MASK |
            XSYSMONPSU_SEQ_CH1_VAUX00_MASK |
            XSYSMONPSU_SEQ_CH1_VAUX01_MASK |
            XSYSMONPSU_SEQ_CH1_VAUX02_MASK |
            XSYSMONPSU_SEQ_CH1_VAUX03_MASK |
            XSYSMONPSU_SEQ_CH1_VAUX04_MASK |
            XSYSMONPSU_SEQ_CH1_VAUX05_MASK |
            XSYSMONPSU_SEQ_CH1_VAUX06_MASK |
            XSYSMONPSU_SEQ_CH1_VAUX07_MASK |
            XSYSMONPSU_SEQ_CH1_VAUX08_MASK |
            XSYSMONPSU_SEQ_CH1_VAUX09_MASK |
            XSYSMONPSU_SEQ_CH1_VAUX0A_MASK |
            XSYSMONPSU_SEQ_CH1_VAUX0B_MASK |
            XSYSMONPSU_SEQ_CH1_VAUX0C_MASK |
            XSYSMONPSU_SEQ_CH1_VAUX0D_MASK |
            XSYSMONPSU_SEQ_CH1_VAUX0E_MASK |
            XSYSMONPSU_SEQ_CH1_VAUX0F_MASK |
			XSYSMONPSU_SEQ_CH0_CALIBRTN_MASK, XSYSMON_PL);
    XSysMonPsu_SetSeqChEnables(SysMonInstPtr, XSYSMONPSU_SEQ_CH0_TEMP_MASK |
			XSYSMONPSU_SEQ_CH0_SUP1_MASK |
			XSYSMONPSU_SEQ_CH0_SUP2_MASK |
			XSYSMONPSU_SEQ_CH0_SUP3_MASK |
            XSYSMONPSU_SEQ_CH0_SUP4_MASK |
            XSYSMONPSU_SEQ_CH0_SUP5_MASK |
            XSYSMONPSU_SEQ_CH0_SUP6_MASK |
            XSYSMONPSU_SEQ_CH0_VP_VN_MASK |
            XSYSMONPSU_SEQ_CH0_VREFP_MASK |
            XSYSMONPSU_SEQ_CH0_VREFN_MASK |
            XSYSMONPSU_SEQ_CH2_SUP7_MASK |
            XSYSMONPSU_SEQ_CH2_SUP8_MASK |
            XSYSMONPSU_SEQ_CH2_SUP9_MASK |
            XSYSMONPSU_SEQ_CH2_SUP10_MASK |
            XSYSMONPSU_SEQ_CH1_VAUX00_MASK |
            XSYSMONPSU_SEQ_CH1_VAUX01_MASK |
            XSYSMONPSU_SEQ_CH1_VAUX02_MASK |
            XSYSMONPSU_SEQ_CH1_VAUX03_MASK |
            XSYSMONPSU_SEQ_CH1_VAUX04_MASK |
            XSYSMONPSU_SEQ_CH1_VAUX05_MASK |
            XSYSMONPSU_SEQ_CH1_VAUX06_MASK |
            XSYSMONPSU_SEQ_CH1_VAUX07_MASK |
            XSYSMONPSU_SEQ_CH1_VAUX08_MASK |
            XSYSMONPSU_SEQ_CH1_VAUX09_MASK |
            XSYSMONPSU_SEQ_CH1_VAUX0A_MASK |
            XSYSMONPSU_SEQ_CH1_VAUX0B_MASK |
            XSYSMONPSU_SEQ_CH1_VAUX0C_MASK |
            XSYSMONPSU_SEQ_CH1_VAUX0D_MASK |
            XSYSMONPSU_SEQ_CH1_VAUX0E_MASK |
            XSYSMONPSU_SEQ_CH1_VAUX0F_MASK |
			XSYSMONPSU_SEQ_CH0_CALIBRTN_MASK, XSYSMON_PL);

    u64 IntrStatus = XSysMonPsu_IntrGetStatus(SysMonInstPtr);
	XSysMonPsu_IntrClear(SysMonInstPtr, IntrStatus);
	XSysMonPsu_SetSequencerMode(SysMonInstPtr, XSM_SEQ_MODE_CONTINPASS, XSYSMON_PS);
    XSysMonPsu_SetSequencerMode(SysMonInstPtr, XSM_SEQ_MODE_CONTINPASS, XSYSMON_PL);
	while ((XSysMonPsu_IntrGetStatus(SysMonInstPtr) & ((u64)XSYSMONPSU_ISR_1_EOS_MASK<< 32)) !=
			((u64)XSYSMONPSU_ISR_1_EOS_MASK<< 32));
}

float sysmon_ps_getTemp(){
    TempRawData = XSysMonPsu_GetAdcData(&SysMonInst, XSM_CH_TEMP, XSYSMON_PS);
	return XSysMonPsu_RawToTemperature_OnChip(TempRawData);
}

float sysmon_ps_getMaxTemp(){
    TempRawData = XSysMonPsu_GetMinMaxMeasurement(&SysMonInst, XSM_MAX_TEMP, XSYSMON_PS);
    return XSysMonPsu_RawToTemperature_OnChip(TempRawData);
}

float sysmon_ps_getMinTemp(){
    TempRawData = XSysMonPsu_GetMinMaxMeasurement(&SysMonInst, XSM_MIN_TEMP, XSYSMON_PS);
    return XSysMonPsu_RawToTemperature_OnChip(TempRawData);
}

float sysmon_ps_getV1(){
    TempRawData = XSysMonPsu_GetAdcData(&SysMonInst, XSM_CH_SUPPLY1, XSYSMON_PS);
    return XSysMonPsu_RawToVoltage(TempRawData);
}

float sysmon_ps_getMaxV1(){
    TempRawData = XSysMonPsu_GetMinMaxMeasurement(&SysMonInst, XSM_MAX_SUPPLY1, XSYSMON_PS);
    return XSysMonPsu_RawToVoltage(TempRawData);
}

float sysmon_ps_getMinV1(){
    TempRawData = XSysMonPsu_GetMinMaxMeasurement(&SysMonInst, XSM_MIN_SUPPLY1, XSYSMON_PS);
    return XSysMonPsu_RawToVoltage(TempRawData);
}

float sysmon_ps_getV2(){
    TempRawData = XSysMonPsu_GetAdcData(&SysMonInst, XSM_CH_SUPPLY2, XSYSMON_PS);
    return XSysMonPsu_RawToVoltage(TempRawData);
}

float sysmon_ps_getMaxV2(){
    TempRawData = XSysMonPsu_GetMinMaxMeasurement(&SysMonInst, XSM_MAX_SUPPLY2, XSYSMON_PS);
    return XSysMonPsu_RawToVoltage(TempRawData);
}

float sysmon_ps_getMinV2(){
    TempRawData = XSysMonPsu_GetMinMaxMeasurement(&SysMonInst, XSM_MIN_SUPPLY2, XSYSMON_PS);
    return XSysMonPsu_RawToVoltage(TempRawData);
}

float sysmon_ps_getV3(){
    TempRawData = XSysMonPsu_GetAdcData(&SysMonInst, XSM_CH_SUPPLY3, XSYSMON_PS);
    return XSysMonPsu_RawToVoltage(TempRawData);
}

float sysmon_ps_getMaxV3(){
    TempRawData = XSysMonPsu_GetMinMaxMeasurement(&SysMonInst, XSM_MAX_SUPPLY3, XSYSMON_PS);
    return XSysMonPsu_RawToVoltage(TempRawData);
}

float sysmon_ps_getMinV3(){
    TempRawData = XSysMonPsu_GetMinMaxMeasurement(&SysMonInst, XSM_MIN_SUPPLY3, XSYSMON_PS);
    return XSysMonPsu_RawToVoltage(TempRawData);
}

float sysmon_ps_getV4(){
    TempRawData = XSysMonPsu_GetAdcData(&SysMonInst, XSM_CH_SUPPLY4, XSYSMON_PS);
    return XSysMonPsu_RawToVoltage(TempRawData);
}

float sysmon_ps_getMaxV4(){
    TempRawData = XSysMonPsu_GetMinMaxMeasurement(&SysMonInst, XSM_MAX_SUPPLY4, XSYSMON_PS);
    return XSysMonPsu_RawToVoltage(TempRawData);
}

float sysmon_ps_getMinV4(){
    TempRawData = XSysMonPsu_GetMinMaxMeasurement(&SysMonInst, XSM_MIN_SUPPLY4, XSYSMON_PS);
    return XSysMonPsu_RawToVoltage(TempRawData);
}

float sysmon_ps_getV5(){
    TempRawData = XSysMonPsu_GetAdcData(&SysMonInst, XSM_CH_SUPPLY5, XSYSMON_PS);
    return XSysMonPsu_RawToVoltage(TempRawData);
}

float sysmon_ps_getMaxV5(){
    TempRawData = XSysMonPsu_GetMinMaxMeasurement(&SysMonInst, XSM_MAX_SUPPLY5, XSYSMON_PS);
    return XSysMonPsu_RawToVoltage(TempRawData);
}

float sysmon_ps_getMinV5(){
    TempRawData = XSysMonPsu_GetMinMaxMeasurement(&SysMonInst, XSM_MIN_SUPPLY5, XSYSMON_PS);
    return XSysMonPsu_RawToVoltage(TempRawData);
}

float sysmon_ps_getV6(){
    TempRawData = XSysMonPsu_GetAdcData(&SysMonInst, XSM_CH_SUPPLY6, XSYSMON_PS);
    return XSysMonPsu_RawToVoltage(TempRawData);
}

float sysmon_ps_getMaxV6(){
    TempRawData = XSysMonPsu_GetMinMaxMeasurement(&SysMonInst, XSM_MAX_SUPPLY6, XSYSMON_PS);
    return XSysMonPsu_RawToVoltage(TempRawData);
}

float sysmon_ps_getMinV6(){
    TempRawData = XSysMonPsu_GetMinMaxMeasurement(&SysMonInst, XSM_MIN_SUPPLY6, XSYSMON_PS);
    return XSysMonPsu_RawToVoltage(TempRawData);
}

float sysmon_ps_getV7(){
    TempRawData = XSysMonPsu_GetAdcData(&SysMonInst, XSM_CH_SUPPLY7, XSYSMON_PS);
    return XSysMonPsu_RawToVoltage(TempRawData);
}

float sysmon_ps_getV8(){
    TempRawData = XSysMonPsu_GetAdcData(&SysMonInst, XSM_CH_SUPPLY8, XSYSMON_PS);
    return XSysMonPsu_RawToVoltage(TempRawData);
}

float sysmon_ps_getV9(){
    TempRawData = XSysMonPsu_GetAdcData(&SysMonInst, XSM_CH_SUPPLY9, XSYSMON_PS);
    return XSysMonPsu_RawToVoltage(TempRawData);
}

float sysmon_ps_getV10(){
    TempRawData = XSysMonPsu_GetAdcData(&SysMonInst, XSM_CH_SUPPLY10, XSYSMON_PS);
    return XSysMonPsu_RawToVoltage(TempRawData);
}

float sysmon_ps_getVpVn(){
    TempRawData = XSysMonPsu_GetAdcData(&SysMonInst, XSM_CH_VPVN, XSYSMON_PS);
    return XSysMonPsu_VpVnRawToVoltage(TempRawData);
}

float sysmon_ps_getVrefP(){
    TempRawData = XSysMonPsu_GetAdcData(&SysMonInst, XSM_CH_VREFP, XSYSMON_PS);
    return XSysMonPsu_RawToVoltage(TempRawData);
}

float sysmon_ps_getVrefN(){
    TempRawData = XSysMonPsu_GetAdcData(&SysMonInst, XSM_CH_VREFN, XSYSMON_PS);
    return XSysMonPsu_RawToVoltage(TempRawData);
}

// PL Functions
float sysmon_pl_getTemp(){
    TempRawData = XSysMonPsu_GetAdcData(&SysMonInst, XSM_CH_TEMP, XSYSMON_PL);
	return XSysMonPsu_RawToTemperature_OnChip(TempRawData);
}

float sysmon_pl_getMaxTemp(){
    TempRawData = XSysMonPsu_GetMinMaxMeasurement(&SysMonInst, XSM_MAX_TEMP, XSYSMON_PL);
    return XSysMonPsu_RawToTemperature_OnChip(TempRawData);
}

float sysmon_pl_getMinTemp(){
    TempRawData = XSysMonPsu_GetMinMaxMeasurement(&SysMonInst, XSM_MIN_TEMP, XSYSMON_PL);
    return XSysMonPsu_RawToTemperature_OnChip(TempRawData);
}

float sysmon_pl_getV1(){
    TempRawData = XSysMonPsu_GetAdcData(&SysMonInst, XSM_CH_SUPPLY1, XSYSMON_PL);
    return XSysMonPsu_RawToVoltage(TempRawData);
}

float sysmon_pl_getMaxV1(){
    TempRawData = XSysMonPsu_GetMinMaxMeasurement(&SysMonInst, XSM_MAX_SUPPLY1, XSYSMON_PL);
    return XSysMonPsu_RawToVoltage(TempRawData);
}

float sysmon_pl_getMinV1(){
    TempRawData = XSysMonPsu_GetMinMaxMeasurement(&SysMonInst, XSM_MIN_SUPPLY1, XSYSMON_PL);
    return XSysMonPsu_RawToVoltage(TempRawData);
}

float sysmon_pl_getV2(){
    TempRawData = XSysMonPsu_GetAdcData(&SysMonInst, XSM_CH_SUPPLY2, XSYSMON_PL);
    return XSysMonPsu_RawToVoltage(TempRawData);
}

float sysmon_pl_getMaxV2(){
    TempRawData = XSysMonPsu_GetMinMaxMeasurement(&SysMonInst, XSM_MAX_SUPPLY2, XSYSMON_PL);
    return XSysMonPsu_RawToVoltage(TempRawData);
}

float sysmon_pl_getMinV2(){
    TempRawData = XSysMonPsu_GetMinMaxMeasurement(&SysMonInst, XSM_MIN_SUPPLY2, XSYSMON_PL);
    return XSysMonPsu_RawToVoltage(TempRawData);
}

float sysmon_pl_getV3(){
    TempRawData = XSysMonPsu_GetAdcData(&SysMonInst, XSM_CH_SUPPLY3, XSYSMON_PL);
    return XSysMonPsu_RawToVoltage(TempRawData);
}

float sysmon_pl_getMaxV3(){
    TempRawData = XSysMonPsu_GetMinMaxMeasurement(&SysMonInst, XSM_MAX_SUPPLY3, XSYSMON_PL);
    return XSysMonPsu_RawToVoltage(TempRawData);
}

float sysmon_pl_getMinV3(){
    TempRawData = XSysMonPsu_GetMinMaxMeasurement(&SysMonInst, XSM_MIN_SUPPLY3, XSYSMON_PL);
    return XSysMonPsu_RawToVoltage(TempRawData);
}

float sysmon_pl_getV4(){
    TempRawData = XSysMonPsu_GetAdcData(&SysMonInst, XSM_CH_SUPPLY4, XSYSMON_PL);
    return XSysMonPsu_RawToVoltage(TempRawData);
}

float sysmon_pl_getMaxV4(){
    TempRawData = XSysMonPsu_GetMinMaxMeasurement(&SysMonInst, XSM_MAX_SUPPLY4, XSYSMON_PL);
    return XSysMonPsu_RawToVoltage(TempRawData);
}

float sysmon_pl_getMinV4(){
    TempRawData = XSysMonPsu_GetMinMaxMeasurement(&SysMonInst, XSM_MIN_SUPPLY4, XSYSMON_PL);
    return XSysMonPsu_RawToVoltage(TempRawData);
}

float sysmon_pl_getV5(){
    TempRawData = XSysMonPsu_GetAdcData(&SysMonInst, XSM_CH_SUPPLY5, XSYSMON_PL);
    return XSysMonPsu_RawToVoltage(TempRawData);
}

float sysmon_pl_getMaxV5(){
    TempRawData = XSysMonPsu_GetMinMaxMeasurement(&SysMonInst, XSM_MAX_SUPPLY5, XSYSMON_PL);
    return XSysMonPsu_RawToVoltage(TempRawData);
}

float sysmon_pl_getMinV5(){
    TempRawData = XSysMonPsu_GetMinMaxMeasurement(&SysMonInst, XSM_MIN_SUPPLY5, XSYSMON_PL);
    return XSysMonPsu_RawToVoltage(TempRawData);
}

float sysmon_pl_getV6(){
    TempRawData = XSysMonPsu_GetAdcData(&SysMonInst, XSM_CH_SUPPLY6, XSYSMON_PL);
    return XSysMonPsu_RawToVoltage(TempRawData);
}

float sysmon_pl_getMaxV6(){
    TempRawData = XSysMonPsu_GetMinMaxMeasurement(&SysMonInst, XSM_MAX_SUPPLY6, XSYSMON_PL);
    return XSysMonPsu_RawToVoltage(TempRawData);
}

float sysmon_pl_getMinV6(){
    TempRawData = XSysMonPsu_GetMinMaxMeasurement(&SysMonInst, XSM_MIN_SUPPLY6, XSYSMON_PL);
    return XSysMonPsu_RawToVoltage(TempRawData);
}

float sysmon_pl_getV7(){
    TempRawData = XSysMonPsu_GetAdcData(&SysMonInst, XSM_CH_SUPPLY7, XSYSMON_PL);
    return XSysMonPsu_RawToVoltage(TempRawData);
}

float sysmon_pl_getMaxV7(){
    TempRawData = XSysMonPsu_GetMinMaxMeasurement(&SysMonInst, XSM_MAX_SUPPLY7, XSYSMON_PL);
    return XSysMonPsu_RawToVoltage(TempRawData);
}

float sysmon_pl_getMinV7(){
    TempRawData = XSysMonPsu_GetMinMaxMeasurement(&SysMonInst, XSM_MIN_SUPPLY7, XSYSMON_PL);
    return XSysMonPsu_RawToVoltage(TempRawData);
}

float sysmon_pl_getV8(){
    TempRawData = XSysMonPsu_GetAdcData(&SysMonInst, XSM_CH_SUPPLY8, XSYSMON_PL);
    return XSysMonPsu_RawToVoltage(TempRawData);
}

float sysmon_pl_getV9(){
    TempRawData = XSysMonPsu_GetAdcData(&SysMonInst, XSM_CH_SUPPLY9, XSYSMON_PL);
    return XSysMonPsu_RawToVoltage(TempRawData);
}

float sysmon_pl_getV10(){
    TempRawData = XSysMonPsu_GetAdcData(&SysMonInst, XSM_CH_SUPPLY10, XSYSMON_PL);
    return XSysMonPsu_RawToVoltage(TempRawData);
}

float sysmon_pl_getVpVn(){
    TempRawData = XSysMonPsu_GetAdcData(&SysMonInst, XSM_CH_VPVN, XSYSMON_PL);
    return XSysMonPsu_VpVnRawToVoltage(TempRawData);
}

float sysmon_pl_getVrefP(){
    TempRawData = XSysMonPsu_GetAdcData(&SysMonInst, XSM_CH_VREFP, XSYSMON_PL);
    return XSysMonPsu_RawToVoltage(TempRawData);
}

float sysmon_pl_getVrefN(){
    TempRawData = XSysMonPsu_GetAdcData(&SysMonInst, XSM_CH_VREFN, XSYSMON_PL);
    return XSysMonPsu_RawToVoltage(TempRawData);
}

float sysmon_pl_getVAux(u8 index){
    TempRawData = XSysMonPsu_GetAdcData(&SysMonInst, XSM_CH_AUX_MIN + index, XSYSMON_PL);
    return XSysMonPsu_RawToVoltage(TempRawData);
}