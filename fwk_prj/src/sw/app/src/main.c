/* FreeRTOS includes */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"

/* LWIP includes */
#include "lwip/init.h"
#include "lwip/inet.h"
#include <stdio.h>
#include "xparameters.h"
#include "netif/xadapter.h"
#include "xil_printf.h"


/* Xilinx includes */
#include "xil_printf.h"
#include "xparameters.h"
#include <assert.h>


/* Hardware support includes */
#include "iic_chp.h"

#define TIMER_ID                1
#define BLINK_TIMER_ID          2
#define DELAY_100_MS            100UL
#define DELAY_1_SECOND          (10*DELAY_100_MS)
#define TIMER_CHECK_THRESHOLD   10
#define DELAY_STOP_HELLO        ((TIMER_CHECK_THRESHOLD+1)*DELAY_1_SECOND)

#define TASK_PRIO_TX_TASK       (tskIDLE_PRIORITY + 2)
#define TASK_PRIO_RX_TASK       (TASK_PRIO_TX_TASK + 1)
#define TASK_PRIO_MENU_TASK     (tskIDLE_PRIORITY + 4)

#define THREAD_STACKSIZE 1024

#define PLATFORM_EMAC_BASEADDR XPAR_XEMACPS_0_BASEADDR

/* The Tx and Rx tasks as described at the top of this file. */
//static void prvTxTask( void *pvParameters );
//static void prvRxTask( void *pvParameters );
//static void prvChpTestTask( void *pvParameters );
//static void vTimerCallback( TimerHandle_t pxTimer );
//static void vBlinkTimerCallback( TimerHandle_t pxTimer );
int main_thread();
void print_echo_app_header();
void psc_control_thread(void *);
void psc_status_thread(void *);
void network_thread(void *);


char HWstring[15] = "Hello World";
long RxtaskCntr = 0;

static struct netif server_netif;
struct netif *echo_netif;


const char *build_date = __DATE__;
const char *build_time = __TIME__;

void init_platform(void)
{
    configIIC(0);
}

void print_ip(char *msg, ip_addr_t *ip)
{
	xil_printf(msg);
	xil_printf("%d.%d.%d.%d\n\r", ip4_addr1(ip), ip4_addr2(ip),
			ip4_addr3(ip), ip4_addr4(ip));
}

void print_ip_settings(ip_addr_t *ip, ip_addr_t *mask, ip_addr_t *gw)
{

	print_ip("Board IP: ", ip);
	print_ip("Netmask : ", mask);
	print_ip("Gateway : ", gw);
}

int main(void)
{
    //const TickType_t xStopTimeTicks = pdMS_TO_TICKS(DELAY_STOP_HELLO);

    xil_printf("Hello PSC example main\r\n");
    init_platform();
    xil_printf("  Initialized platform\r\n\r\n");

	sys_thread_new("main_thrd", (void(*)(void*))main_thread, 0,
	                THREAD_STACKSIZE,
	                DEFAULT_THREAD_PRIO);


    /* Start the tasks and timer running. */
    vTaskStartScheduler();

    /* If all is well, the scheduler will now be running, and the following line
    will never be reached.  If the following line does execute, then there was
    insufficient FreeRTOS heap memory available for the idle and/or timer tasks
    to be created.  See the memory management section on the FreeRTOS web site
    for more details. */
    xil_printf("!!! We shouldn't have reached here !!!\r\n");
    for (;;)
        ;

    return 0;
}

int main_thread()
{
	/* initialize lwIP before calling sys_thread_new */
    lwip_init();

    /* any thread using lwIP should be created using sys_thread_new */
    sys_thread_new("NW_THRD", network_thread, NULL, THREAD_STACKSIZE, DEFAULT_THREAD_PRIO);

    vTaskDelete(NULL);
    return 0;
}

void network_thread(void *p)
{
	const TickType_t x1second = pdMS_TO_TICKS(DELAY_1_SECOND);
    struct netif *netif;
    /* the mac address of the board. this should be unique per board */
    unsigned char mac_ethernet_address[] = { 0x00, 0x0a, 0x35, 0x00, 0x01, 0x02 };
    ip_addr_t ipaddr, netmask, gw;

    netif = &server_netif;

    /* initialize IP addresses to be used */
    IP4_ADDR(&ipaddr,  192, 168, 1, 10);
    IP4_ADDR(&netmask, 255, 255, 255,  0);
    IP4_ADDR(&gw,      10, 0, 142, 5);

    /* print out IP settings of the board */
    print_ip_settings(&ipaddr, &netmask, &gw);

    /* Add network interface to the netif_list, and set it as default */
    if (!xemac_add(netif, &ipaddr, &netmask, &gw, mac_ethernet_address, PLATFORM_EMAC_BASEADDR)) {
	xil_printf("Error adding N/W interface\r\n");
	return;
    }

    netif_set_default(netif);

    /* specify that the network if is up */
    netif_set_up(netif);

    /* start packet receive thread - required for lwIP operation */
    sys_thread_new("xemacif_input_thread", (void(*)(void*))xemacif_input_thread, netif,
            THREAD_STACKSIZE,
            DEFAULT_THREAD_PRIO);

    /* Delay for 1 second. */
    vTaskDelay(x1second);

    // Start the PSC Control Thread.  Handles incoming commands from IOC
    xil_printf("\r\n");
    sys_thread_new("psc_cntrl_thread", psc_control_thread, 0,
		THREAD_STACKSIZE,
		DEFAULT_THREAD_PRIO);

    /* Delay for 1 second. */
    vTaskDelay(x1second);

    // Start the PSC Control Thread.  Handles incoming commands from IOC
    sys_thread_new("psc_status_thread", psc_status_thread, 0,
		THREAD_STACKSIZE,
		DEFAULT_THREAD_PRIO);
    vTaskDelete(NULL);

    return;
}





