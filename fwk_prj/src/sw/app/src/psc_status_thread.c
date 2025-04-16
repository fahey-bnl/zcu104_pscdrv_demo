/********************************************************************
*  PSC Status Thread
*  J. Mead
*  4-17-24
*
*  This thread is responsible for sending all slow data (10Hz) to the IOC.   It does
*  this over to message ID's (30 = slow status, 31 = 10Hz data)
*
*  It starts a listening server on
*  port 600.  Upon establishing a connection with a client, it begins to send out
*  packets containing all 10Hz updated data.
********************************************************************/

#include <stdio.h>
#include <string.h>

#include "lwip/sockets.h"
#include "netif/xadapter.h"
#include "lwipopts.h"
#include "xil_printf.h"
#include "FreeRTOS.h"
#include "task.h"

#include "sysmon_chp.h"

#define THREAD_STACKSIZE 1024
#define PORT  600

//The PSC interface defines many different MsgID's
#define MSGHDRLEN 8

//This message is for slow status
#define MSGID30 30
#define MSGID30LEN 748   //in bytes

// System Health Status Readback offsets
// 1Hz
#define TEMP_SENSE0_MSGOFF 0
#define TEMP_SENSE1_MSGOFF 4
#define TEMP_SENSE2_MSGOFF 8
#define TEMP_SENSE3_MSGOFF 12

#define DELAY_1_SECOND            1000UL

void Host2NetworkConvStatus(char *inbuf, char *outbuf) {

    int i;

    for (i=0;i<8;i++)
        outbuf[i] = inbuf[i];
    for (i=8;i<MSGID30LEN;i=i+4) {
        //printf("In %d: %d %d %d %d\n",i,inbuf[i],inbuf[i+1],inbuf[i+2],inbuf[i+3]);
        outbuf[i] = inbuf[i+3];
        outbuf[i+1] = inbuf[i+2];
        outbuf[i+2] = inbuf[i+1];
        outbuf[i+3] = inbuf[i];
        //printf("Out %d: %d %d %d %d\n\n",i,outbuf[i],outbuf[i+1],outbuf[i+2],outbuf[i+3]);
    }
}

void ReadBrdTemp(u32 tdev, char *msg) {
	float temp;

	switch(tdev){
		case 0:
			temp = sysmon_ps_temp;
			break;
		case 1:
			temp = sysmon_pl_temp;
			break;
		case 3:
			temp = sysmon_vcc_int;
			break;
		default:
			temp = sysmon_vcc_bram;
	}

    printf("Dev %d: temp = %0.2f\r\n",
           tdev, temp);
    memcpy(msg,&temp,sizeof(s32));
}

void ReadSysInfo(char *msg) {
	// Read the 4 CHP Temperature Sensors
	ReadBrdTemp(0,&msg[TEMP_SENSE0_MSGOFF]);
	ReadBrdTemp(1,&msg[TEMP_SENSE1_MSGOFF]);
	ReadBrdTemp(2,&msg[TEMP_SENSE2_MSGOFF]);
	ReadBrdTemp(3,&msg[TEMP_SENSE3_MSGOFF]);
}

void psc_status_thread()
{
	const TickType_t x1second = pdMS_TO_TICKS(DELAY_1_SECOND);
	int sockfd, newsockfd;
	int clilen;
	struct sockaddr_in serv_addr, cli_addr;
    char msgid30_buf[1024];
    char msgid30_bufntoh[1024];
    int *msgid30_bufptr;
    int n;

    xil_printf("Starting PSC Status Server...\r\n");

	// Initialize socket structure
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);
	serv_addr.sin_addr.s_addr = INADDR_ANY;

    // First call to socket() function
	if ((sockfd = lwip_socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		xil_printf("Error: PSC Status : Creating Socket");
		vTaskDelete(NULL);
	}

    // Bind to the host address using bind()
	if (lwip_bind(sockfd, (struct sockaddr *)&serv_addr, sizeof (serv_addr)) < 0) {
		xil_printf("Error: PSC Status : Creating Socket");
		vTaskDelete(NULL);
	}

    // Now start listening for the clients
	lwip_listen(sockfd, 0);

    xil_printf("PSC Status Server listening on port %d...\r\n",PORT);

reconnect:

	clilen = sizeof(cli_addr);

	newsockfd = lwip_accept(sockfd, (struct sockaddr *)&cli_addr, (socklen_t *)&clilen);
	if (newsockfd < 0) {
	    xil_printf("ERROR on accept\r\n");
	    vTaskDelete(NULL);
	}
	/* If connection is established then start communicating */
	xil_printf("PSC Status: Connected Accepted...\r\n");

    //initialize the 1Hz status registers
    bzero(msgid30_buf,sizeof(msgid30_buf));
    msgid30_bufptr = (int *)msgid30_buf;
    msgid30_buf[0] = 'P';
    msgid30_buf[1] = 'S';
    msgid30_buf[2] = 0;
    msgid30_buf[3] = (short int) MSGID30;
    *++msgid30_bufptr = htonl(MSGID30LEN);  //body length

    xil_printf("PSC Status: Entering while loop...\r\n");

	while (1) {
		xil_printf("In main loop...\r\n");

		ReadSysInfo(&msgid30_buf[MSGHDRLEN]);
		xil_printf("\r\n");
		
        vTaskDelay(x1second);

		Host2NetworkConvStatus(msgid30_buf,msgid30_bufntoh);
		n = write(newsockfd,msgid30_bufntoh,MSGID30LEN+MSGHDRLEN);
	        if (n < 0) {
	           printf("Status socket: ERROR writing MSG 30 - 1Hz Info\n");
	           close(newsockfd);
	           goto reconnect;
	        }
	}

	/* close connection */
	close(newsockfd);
	vTaskDelete(NULL);
}


