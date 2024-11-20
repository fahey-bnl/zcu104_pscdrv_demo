/**
 * Base driver for all IIC communications on the Zynq MPSoC
 * 
 * All i2c connections are tunneled through port enablers at 0x70, 0x71, and 0x72
 * 
 * Connections at 0x70:
 * 0-7: SFP Connector- handled through iic_sfp_* and iic_rx_los in iic_misc
 * 
 * Connections at 0x71:
 * 0: Temperature Sensor- handled through iic_temp in iic_misc
 * 1: Not connected
 * 2: LTC2991- handled through functions in iic_ltc2991
 * 3: LTC2977- handled through functions in iic_pmbus
 * 4: Daughterboard 0- handled through iic_db0_enable/disable
 * 5: Daughterboard 1- handled through iic_db1_enable/disable
 * 6: ADN4612- handled through functions in iic_xpt
 * 7: TCA9554PWR- handled through functions in iic_set_power_on
 * 
 * Connections at 0x72:
 * 0: 24AA025E48- handled through functions in iic_eeprom_* and iic_get_mac_address
 * 1: SI570 (Currently being replaced by either a LMK61E2 or a LMK61E2-156M)
 * 2: TCA9554PWR- handled through functions in iic_set_gpio_dir
 * 3: TCA9554PWR- handled through functions in iic_*_sfp_txdisable
 * 4: Expansion Header- handled through iic_expansionhdr_enable/disable
 * 5: Spare 0- handled through iic_spare0_enable/disable
 * 6: Spare 1- handled through iic_spare1_enable/disable
 * 7: AMC6821- handled through functions in iic_fan
 * 
*/

#ifndef __IIC_CHP_H
#define __IIC_CHP_H

#ifdef USING_FREERTOS
#include "FreeRTOS.h"
#include "semphr.h"
#endif

#include "xparameters.h"
#include "xiicps.h"
#include "xil_printf.h"
#include "xplatform_info.h"


#define IIC_SCLK_RATE 100000

#ifdef USING_FREERTOS
static SemaphoreHandle_t iic_mutex;
#endif

/**
 * @brief configures the I2C bus, must be run before any i2c commands
 * @param deviceID I2C device ID
*/
int configIIC(u16 deviceID);

/**
 * @brief sends bytes of data to the i2c address specified, waiting for the bus to not be busy before sending
 * @param writeBuffer array of bytes to write
 * @param len length of array
 * @param addr address of i2c device
*/
void iic_chp_send(u8 * writeBuffer, u8 len, u8 addr);

/**
 * @brief reads bytes of data sent over the i2c bus
 * @param readBuffer array of bytes to be read to
 * @param addr address of i2c device to be read from
*/
void iic_chp_recv(u8 * readBuffer, u8 len, u8 addr);

/**
 * @brief sends bytes of data to the i2c address specified, with flag for repeated start condition set
 * @param writeBuffer array of bytes to write
 * @param len length of array
 * @param addr address of i2c device
*/
void iic_chp_send_repeated_start(u8 * writeBuffer, u8 len, u8 addr);

/**
 * @brief reads bytes of data sent over the i2c bus, for use after send with repeated start flag
 * @param readBuffer array of bytes to be read to
 * @param addr address of i2c device to be read from
 * @note does not wait on previous transaction to finish, unlike normal iic_chp_recv function
*/
void iic_chp_recv_after_repeated_start(u8 * readBuffer, u8 len, u8 addr);

/**
 * @brief combines the functions handled by send_repeated_start and recv_after_repeated_start, used for receiving bytes at an address
 * @param addrBuf array of bytes that define the address
 * @param addrLen length of addrBuf array
 * @param recvBuf array of bytes to receive the data
 * @param recvLen length of recvBuf array
 * @param addr i2c address of device to read from
*/
void iic_chp_recv_repeated_start(u8 * addrBuf, u8 addrLen, u8* recvBuf, u8 recvLen, u8 addr);

/**
 * @brief confirms a device is connected over i2c
 * @param address address to confirm
*/
s32 iic_confirm_slave(u8 address);

/**
 * @brief enables a port using the IIC port expander
 * @param pe port expander to talk to
 * @param index port to enable on the expander
 * @note All ports enabled with this function must be disabled by iic_pe_disable once they are finished being used to avoid mutex issues
*/
void iic_pe_enable(u8 pe, u8 index);

/**
 * @brief disables a port using the IIC port expander
 * @param pe port expander to talk to
 * @param index port to disable on the expander
*/
void iic_pe_disable(u8 pe, u8 index);

/**
 * @brief writes all values of a port expander
 * @param pe port expander to write to
 * @param val value to write to expander
*/
void iic_pe_write(u8 pe, u8 val);
/**
 * @brief reads the value from a port expander
 * @param pe port expander to read from
 * @returns status of all outputs
*/
u8 iic_pe_read(u8 pe);

/**
 * @brief enables i2c communication to Daughterboard 0
*/
void iic_db0_enable();
/**
 * @brief disables i2c communication to Daughterboard 0
*/
void iic_db0_disable();
/**
 * @brief enables i2c communication to Daughterboard 1
*/
void iic_db1_enable();
/**
 * @brief disables i2c communication to Daughterboard 1
*/
void iic_db1_disable();
/**
 * @brief enables i2c communication to the expansion header
*/
void iic_expansionhdr_enable();
/**
 * @brief disables i2c communication to the expansion header
*/
void iic_expansionhdr_disable();
/**
 * @brief enables i2c communication over the spare 0 header
*/
void iic_spare0_enable();
/**
 * @brief disables i2c communication over the spare 0 header
*/
void iic_spare0_disable();
/**
 * @brief enables i2c communication over the spare 1 header
*/
void iic_spare1_enable();
/**
 * @brief disables i2c communication over the spare 1 header
*/
void iic_spare1_disable();

#endif /* __IIC_CHP_H */
