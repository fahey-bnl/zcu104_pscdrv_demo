#include "iic_chp.h"

static XIicPs IicInstance;

static const u8 iic_pe_addrs[] = {0x70, 0x71, 0x72};
static u8 iic_pe_status[] = {0x00, 0x00, 0x00};

int configIIC(u16 DeviceID){
    s32 Status;
    XIicPs_Config* ConfigPtr;

    #ifdef USING_FREERTOS
    iic_mutex = xSemaphoreCreateRecursiveMutex();
    #endif

    ConfigPtr = XIicPs_LookupConfig(DeviceID);
    if(ConfigPtr == NULL) return XST_FAILURE;

    Status = XIicPs_CfgInitialize(&IicInstance, ConfigPtr, ConfigPtr->BaseAddress);
    if(Status != XST_SUCCESS) return XST_FAILURE;

    XIicPs_SetSClk(&IicInstance, IIC_SCLK_RATE);

    for(int i = 0; i < 3; i++) iic_pe_write(i, 0x00);

    return XST_SUCCESS;
}

void iic_chp_send(u8 * writeBuffer, u8 len, u8 addr){
    #ifdef USING_FREERTOS
    while(xSemaphoreTakeRecursive(iic_mutex, portMAX_DELAY) != pdTRUE);
    #endif
    while (XIicPs_BusIsBusy(&IicInstance)); //Make sure bus is not busy
    XIicPs_MasterSendPolled(&IicInstance, writeBuffer, len, addr);
    #ifdef USING_FREERTOS
    xSemaphoreGiveRecursive(iic_mutex);
    #endif
}

void iic_chp_recv(u8 * readBuffer, u8 len, u8 addr){
    #ifdef USING_FREERTOS
    while(xSemaphoreTakeRecursive(iic_mutex, portMAX_DELAY) != pdTRUE);
    #endif
    while (XIicPs_BusIsBusy(&IicInstance)); //Make sure bus is not busy
    XIicPs_MasterRecvPolled(&IicInstance, readBuffer, len, addr);
    #ifdef USING_FREERTOS
    xSemaphoreGiveRecursive(iic_mutex);
    #endif
}

// see https://github.com/Xilinx/embeddedsw/blob/master/XilinxProcessorIPLib/drivers/iicps/examples/xiicps_repeated_start_example.c
// for info about i2c repeated start
// ADT7410 seems to require repeated start in order to work. The TCA9554
// datasheet shows repeated start used for reads, but I did not test the
// TCA9554 without using repeated start. 
void iic_chp_send_repeated_start(u8 * writeBuffer, u8 len, u8 addr){
    #ifdef USING_FREERTOS
    while(xSemaphoreTakeRecursive(iic_mutex, portMAX_DELAY) != pdTRUE);
    #endif
    while (XIicPs_BusIsBusy(&IicInstance)); //Make sure bus is not busy
    XIicPs_SetOptions(&IicInstance, XIICPS_REP_START_OPTION);
    XIicPs_MasterSendPolled(&IicInstance, writeBuffer, len, addr);
	XIicPs_ClearOptions(&IicInstance, XIICPS_REP_START_OPTION);
    #ifdef USING_FREERTOS
    xSemaphoreGiveRecursive(iic_mutex);
    #endif
}

void iic_chp_recv_after_repeated_start(u8 * readBuffer, u8 len, u8 addr){
    #ifdef USING_FREERTOS
    while(xSemaphoreTakeRecursive(iic_mutex, portMAX_DELAY) != pdTRUE);
    #endif
    // do not wait for previous transaction to complete when doing repeated start
    XIicPs_MasterRecvPolled(&IicInstance, readBuffer, len, addr);
    #ifdef USING_FREERTOS
    xSemaphoreGiveRecursive(iic_mutex);
    #endif
}

//Combining the two above functions, as they work with each other
void iic_chp_recv_repeated_start(u8 * addrBuf, u8 addrLen, u8* recvBuf, u8 recvLen, u8 addr){
    #ifdef USING_FREERTOS
    while(xSemaphoreTakeRecursive(iic_mutex, portMAX_DELAY) != pdTRUE);
    #endif

    while (XIicPs_BusIsBusy(&IicInstance)); //Make sure bus is not busy
    XIicPs_SetOptions(&IicInstance, XIICPS_REP_START_OPTION);
    XIicPs_MasterSendPolled(&IicInstance, addrBuf, addrLen, addr);
	XIicPs_ClearOptions(&IicInstance, XIICPS_REP_START_OPTION);
    XIicPs_MasterRecvPolled(&IicInstance, recvBuf, recvLen, addr);

    #ifdef USING_FREERTOS
    xSemaphoreGiveRecursive(iic_mutex);
    #endif
}

s32 iic_confirm_slave(u8 address){
    u32 Index = 0;
    u16 IntrStatusReg;

    #ifdef USING_FREERTOS
    while(xSemaphoreTakeRecursive(iic_mutex, portMAX_DELAY) != pdTRUE);
    #endif
    XIicPs_EnableSlaveMonitor(&IicInstance, address);
    while(Index < 0x00FFFFFF){
		Index++;
		IntrStatusReg = XIicPs_ReadReg((&IicInstance)->Config.BaseAddress,(u32)XIICPS_ISR_OFFSET);
		if(0U != (IntrStatusReg & XIICPS_IXR_SLV_RDY_MASK)){
			XIicPs_DisableSlaveMonitor(&IicInstance);
			XIicPs_WriteReg((&IicInstance)->Config.BaseAddress,(u32)XIICPS_ISR_OFFSET,IntrStatusReg);
			xil_printf("Device Found\n");
            #ifdef USING_FREERTOS
            xSemaphoreGiveRecursive(iic_mutex);
            #endif
			return XST_SUCCESS;
		}
	}
    XIicPs_DisableSlaveMonitor(&IicInstance);
    #ifdef USING_FREERTOS
    xSemaphoreGiveRecursive(iic_mutex);
    #endif
    return XST_FAILURE;
}

void iic_pe_enable(u8 pe, u8 index){
    #ifdef USING_FREERTOS
    while(xSemaphoreTakeRecursive(iic_mutex, portMAX_DELAY) != pdTRUE);
    #endif
    iic_pe_status[pe] = iic_pe_status[pe] | (0x01<<index);
    iic_chp_send(iic_pe_status + pe, 1, iic_pe_addrs[pe]);
}

void iic_pe_disable(u8 pe, u8 index){
    iic_pe_status[pe] = iic_pe_status[pe] & (0xFF - (0x01<<index));
    iic_chp_send(iic_pe_status + pe, 1, iic_pe_addrs[pe]);
    #ifdef USING_FREERTOS
    xSemaphoreGiveRecursive(iic_mutex);
    #endif
}

void iic_pe_write(u8 pe, u8 val){
    iic_pe_status[pe] = val;
    iic_chp_send(iic_pe_status + pe, 1, iic_pe_addrs[pe]);
}

u8 iic_pe_read(u8 pe){
    u8 buf[1];
    iic_chp_recv(buf, 1, iic_pe_addrs[pe]);
    iic_pe_status[pe] = buf[0];
    return buf[0];
}

void iic_db0_enable(){
    iic_pe_enable(1, 4);
}
void iic_db0_disable(){
    iic_pe_disable(1, 4);
}
void iic_db1_enable(){
    iic_pe_enable(1, 5);
}
void iic_db1_disable(){
    iic_pe_disable(1, 5);
}
void iic_expansionhdr_enable(){
    iic_pe_enable(2, 4);
}
void iic_expansionhdr_disable(){
    iic_pe_disable(2, 4);
}
void iic_spare0_enable(){
    iic_pe_enable(2, 5);
}
void iic_spare0_disable(){
    iic_pe_disable(2, 5);
}
void iic_spare1_enable(){
    iic_pe_enable(2, 6);
}
void iic_spare1_disable(){
    iic_pe_disable(2, 6);
}
