#ifndef __SYSMON_CHP_H
#define __SYSMON_CHP_H

#include "xsysmonpsu.h"

// PS Side Temperature
#define sysmon_ps_temp sysmon_ps_getTemp()
#define sysmon_max_ps_temp sysmon_ps_getMaxTemp()
#define sysmon_min_ps_temp sysmon_ps_getMinTemp()

// PL Side Temperature
#define sysmon_pl_temp sysmon_pl_getTemp()
#define sysmon_max_pl_temp sysmon_pl_getMaxTemp()
#define sysmon_min_pl_temp sysmon_pl_getMinTemp()

// Power Supply Internal Low Power (0.85/0.9V)
#define sysmon_ps_int_lp sysmon_ps_getV1()
#define sysmon_max_ps_int_lp sysmon_ps_getMaxV1()
#define sysmon_min_ps_int_lp sysmon_ps_getMinV1()

// Power Supply Internal Full Power (0.85/0.9V)
#define sysmon_ps_int_fp sysmon_ps_getV2()
#define sysmon_max_ps_int_fp sysmon_ps_getMaxV2()
#define sysmon_min_ps_int_fp sysmon_ps_getMinV2()

// Power Supply Auxillary Power (1.8V)
#define sysmon_ps_aux sysmon_ps_getV3()
#define sysmon_max_ps_aux sysmon_ps_getMaxV3()
#define sysmon_min_ps_aux sysmon_ps_getMinV3()

// Power Supply DDR Filter (1.8V)
#define sysmon_ps_ddr sysmon_ps_getV4()
#define sysmon_max_ps_ddr sysmon_ps_getMaxV4()
#define sysmon_min_ps_ddr sysmon_ps_getMinV4()

// Power Supply IO Pin 3 (1.8-3.3V)
#define sysmon_ps_io3 sysmon_ps_getV5()
#define sysmon_max_ps_io3 sysmon_ps_getMaxV5()
#define sysmon_min_ps_io3 sysmon_ps_getMinV5()

// Power Supply IO Pin 0 (1.8-3.3V)
#define sysmon_ps_io0 sysmon_ps_getV6()
#define sysmon_max_ps_io0 sysmon_ps_getMaxV6()
#define sysmon_min_ps_io0 sysmon_ps_getMinV6()

// MPSoC Internal Voltage (0.85/0.9V)
#define sysmon_vcc_int sysmon_pl_getV1()
#define sysmon_max_vcc_int sysmon_pl_getMaxV1()
#define sysmon_min_vcc_int sysmon_pl_getMinV1()

// MPSoC Auxillary Voltage (1.8V)
#define sysmon_vcc_aux sysmon_pl_getV2()
#define sysmon_max_vcc_aux sysmon_pl_getMaxV2()
#define sysmon_min_vcc_aux sysmon_pl_getMinV2()

// MPSoC BRAM Voltage (0.85/0.9V)
#define sysmon_vcc_bram sysmon_pl_getV3()
#define sysmon_max_vcc_bram sysmon_pl_getMaxV3()
#define sysmon_min_vcc_bram sysmon_pl_getMinV3()

// VP/VN Analog Signal
#define sysmon_vpvn sysmon_ps_getVpVn()

// ADC/DAC VrefP
#define sysmon_vrefp sysmon_ps_getVrefP()

// ADC/DAC VrefN
#define sysmon_vrefn sysmon_ps_getVrefN()

/**
 * @brief initializes the sysmon's monitoring
*/
void sysmon_init();
/**
 * @brief gets the on-chip temperature for the PS
*/
float sysmon_ps_getTemp();
/**
 * @brief gets the maximum read on-chip temperature for the PS
*/
float sysmon_ps_getMaxTemp();
/**
 * @brief gets the minimum read on-chip temperature for the PS
*/
float sysmon_ps_getMinTemp();
/**
 * @brief gets the Supply 1 (VCC PS Int LP) voltage
*/
float sysmon_ps_getV1();
/**
 * @brief gets the maximum read Supply 1 (VCC PS Int LP) voltage
*/
float sysmon_ps_getMaxV1();
/**
 * @brief gets the minimum read Supply 1 (VCC PS Int LP) voltage
*/
float sysmon_ps_getMinV1();
/**
 * @brief gets the Supply 2 (VCC PS Int FP) voltage
*/
float sysmon_ps_getV2();
/**
 * @brief gets the maximum read Supply 2 (VCC PS Int FP) voltage
*/
float sysmon_ps_getMaxV2();
/**
 * @brief gets the minimum read Supply 2 (VCC PS Int FP) voltage
*/
float sysmon_ps_getMinV2();
/**
 * @brief gets the Supply 3 (VCC PS Aux) voltage
*/
float sysmon_ps_getV3();
/**
 * @brief gets the maximum read Supply 3 (VCC PS Aux) voltage
*/
float sysmon_ps_getMaxV3();
/**
 * @brief gets the minimum read Supply 3 (VCC PS Aux) voltage
*/
float sysmon_ps_getMinV3();
/**
 * @brief gets the Supply 4 (VCC PS DDR) voltage
*/
float sysmon_ps_getV4();
/**
 * @brief gets the maximum read Supply 4 (VCC PS DDR) voltage
*/
float sysmon_ps_getMaxV4();
/**
 * @brief gets the minimum read Supply 4 (VCC PS DDR) voltage
*/
float sysmon_ps_getMinV4();
/**
 * @brief gets the Supply 5 (VCC PSIO 3) voltage
*/
float sysmon_ps_getV5();
/**
 * @brief gets the maximum read Supply 5 (VCC PSIO 3) voltage
*/
float sysmon_ps_getMaxV5();
/**
 * @brief gets the minimum read Supply 5 (VCC PSIO 3) voltage
*/
float sysmon_ps_getMinV5();
/**
 * @brief gets the Supply 6 (VCC PSIO 0) voltage
*/
float sysmon_ps_getV6();
/**
 * @brief gets the maximum read Supply 6 (VCC PSIO 0) voltage
*/
float sysmon_ps_getMaxV6();
/**
 * @brief gets the minimum read Supply 6 (VCC PSIO 0) voltage
*/
float sysmon_ps_getMinV6();

float sysmon_ps_getV7();
float sysmon_ps_getV8();
float sysmon_ps_getV9();
float sysmon_ps_getV10();

/**
 * @brief gets the value of the Vp/Vn dedicated analog inputs
*/
float sysmon_ps_getVpVn();
/**
 * @brief gets the value of VRefP
*/
float sysmon_ps_getVrefP();
/**
 * @brief gets the value of VRefN
*/
float sysmon_ps_getVrefN();

/**
 * @brief gets the on-chip temperature for the PL
*/
float sysmon_pl_getTemp();
/**
 * @brief gets the maximum read on-chip temperature for the PL
*/
float sysmon_pl_getMaxTemp();
/**
 * @brief gets the minimum read on-chip temperature for the PL
*/
float sysmon_pl_getMinTemp();
/**
 * @brief gets the Supply 1 (VCC Int) voltage
*/
float sysmon_pl_getV1();
/**
 * @brief gets the maximum read Supply 1 (VCC Int) voltage
*/
float sysmon_pl_getMaxV1();
/**
 * @brief gets the minimum read Supply 1 (VCC Int) voltage
*/
float sysmon_pl_getMinV1();
/**
 * @brief gets the Supply 2 (VCC Aux) voltage
*/
float sysmon_pl_getV2();
/**
 * @brief gets the maximum read Supply 2 (VCC Aux) voltage
*/
float sysmon_pl_getMaxV2();
/**
 * @brief gets the minimum read Supply 2 (VCC Aux) voltage
*/
float sysmon_pl_getMinV2();
// VCC BRAM
/**
 * @brief gets the Supply 3 (VCC BRAM) voltage
*/
float sysmon_pl_getV3();
/**
 * @brief gets the maximum read Supply 3 (VCC BRAM) voltage
*/
float sysmon_pl_getMaxV3();
/**
 * @brief gets the minimum read Supply 3 (VCC BRAM) voltage
*/
float sysmon_pl_getMinV3();
// VCC PS Int LP, redundant
/**
 * @brief gets the Supply 4 (VCC PS Int LP) voltage
 * @note redundant, same functionality achieved through `sysmon_ps_getV1()`
*/
float sysmon_pl_getV4();
/**
 * @brief gets the maximum read Supply 4 (VCC PS Int LP) voltage
 * @note redundant, same functionality achieved through `sysmon_ps_getMaxV1()`
*/
float sysmon_pl_getMaxV4();
/**
 * @brief gets the minimum read Supply 4 (VCC PS Int LP) voltage
 * @note redundant, same functionality achieved through `sysmon_ps_getMinV1()`
*/
float sysmon_pl_getMinV4();
// VCC PS Int FP, redundant
/**
 * @brief gets the Supply 5 (VCC PS Int FP) voltage
 * @note redundant, same functionality achieved through `sysmon_ps_getV2()`
*/
float sysmon_pl_getV5();
/**
 * @brief gets the maximum read Supply 5 (VCC PS Int FP) voltage
 * @note redundant, same functionality achieved through `sysmon_ps_getMaxV2()`
*/
float sysmon_pl_getMaxV5();
/**
 * @brief gets the minimum read Supply 5 (VCC PS Int FP) voltage
 * @note redundant, same functionality achieved through `sysmon_ps_getMinV2()`
*/
float sysmon_pl_getMinV5();
//VCC PS Aux, redundant
/**
 * @brief gets the Supply 6 (VCC PS Int LP) voltage
 * @note redundant, same functionality achieved through `sysmon_ps_getV3()`
*/
float sysmon_pl_getV6();
/**
 * @brief gets the maximum read Supply 6 (VCC PS Int LP) voltage
 * @note redundant, same functionality achieved through `sysmon_ps_getMaxV3()`
*/
float sysmon_pl_getMaxV6();
/**
 * @brief gets the minimum read Supply 6 (VCC PS Int LP) voltage
 * @note redundant, same functionality achieved through `sysmon_ps_getMinV3()`
*/
float sysmon_pl_getMinV6();

float sysmon_pl_getV7();
float sysmon_pl_getV8();
float sysmon_pl_getV9();
float sysmon_pl_getV10();

/**
 * @brief gets the value of the Vp/Vn dedicated analog inputs
*/
float sysmon_pl_getVpVn();
/**
 * @brief gets the value of VRefP
*/
float sysmon_pl_getVrefP();
/**
 * @brief gets the value of VRefN
*/
float sysmon_pl_getVrefN();

float sysmon_pl_getVAux(u8 index);

#endif
