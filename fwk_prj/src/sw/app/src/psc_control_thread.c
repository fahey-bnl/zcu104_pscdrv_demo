/********************************************************************
*  PSC Status Thread
*  J. Mead
*  4-17-24
*
*  This thread is responsible for receiving all control info from the IOC.   It does
*  this over to message ID 1)
*
*  It starts a listening server on port 7.
*  Upon establishing a connection with a client, it waits to receive
*  packets containing control information from the IOC
********************************************************************/

#include <stdio.h>
#include <string.h>

#include "lwip/sockets.h"
#include "netif/xadapter.h"
#include "lwipopts.h"
#include "xil_printf.h"
#include "FreeRTOS.h"
#include "task.h"

#include "sampleVars.h"

#define THREAD_STACKSIZE 1024
#define PORT  7

#define REG_ID 4
#define DOUBLE_ID 5

void psc_control_thread()
{
	int sockfd, newsockfd;
	int clilen;
	struct sockaddr_in serv_addr, cli_addr;
	int RECV_BUF_SIZE = 2048;
	char buffer[RECV_BUF_SIZE];
	int n, *bufptr, numpackets=0;
    int MsgAddr, MsgData, MsgID;

    xil_printf("Starting PSC Control Server...\r\n");

	// Initialize socket structure
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);
	serv_addr.sin_addr.s_addr = INADDR_ANY;

    // First call to socket() function
	if ((sockfd = lwip_socket(AF_INET, SOCK_STREAM, 0)) < 0)
		exit(1);

    // Bind to the host address using bind()
	if (lwip_bind(sockfd, (struct sockaddr *)&serv_addr, sizeof (serv_addr)) < 0)
		exit(1);

    // Now start listening for the clients
	lwip_listen(sockfd, 0);


    xil_printf("Server listening on port %d...\r\n",PORT);


reconnect:

	clilen = sizeof(cli_addr);

	newsockfd = lwip_accept(sockfd, (struct sockaddr *)&cli_addr, (socklen_t *)&clilen);
	if (newsockfd < 0) {
	    xil_printf("ERROR on accept\r\n");
	    exit(1);
	}
	/* If connection is established then start communicating */
	xil_printf("Connected Accepted...\r\n");

	while (1) {
		/* read a max of RECV_BUF_SIZE bytes from socket */
		n = read(newsockfd, buffer, RECV_BUF_SIZE);
        if (n <= 0) {
            xil_printf("ERROR reading from socket..  Reconnecting...\n");
            close(newsockfd);
	        goto reconnect;
        }

        bufptr = (int *) buffer;
        xil_printf("\nPacket %d Received : NumBytes = %d\r\n",++numpackets,n);
        xil_printf("Header: %c%c \t",buffer[0],buffer[1]);
		MsgID = (ntohl(*bufptr++)&0xFFFF);
        xil_printf("Message ID : %d\t",MsgID);
        xil_printf("Body Length : %d\t",ntohl(*bufptr++));

        switch(MsgID) {
		case REG_ID:
			MsgAddr = ntohl(*bufptr++);
			xil_printf("Msg Addr : %d\t",MsgAddr);
			MsgData = ntohl(*bufptr);
			xil_printf("Data : %d\r\n",MsgData);

			switch(MsgAddr){
			case 0:
				memcpy(SAMPLE_INT, &MsgData, sizeof(s32));
				break;
			case 1:
				memcpy(SAMPLE_FLOAT, &MsgData, sizeof(s32));
				break;
			default:
				xil_printf("Unsupported Register\r\n");
				break;
			}
			break;
		case DOUBLE_ID:
			u32 high = ntohl(*bufptr++);
			u32 low = ntohl(*bufptr);
			xil_printf("Data: 0x%4X %4X\n", high, low);

			memcpy(SAMPLE_DOUBLE, &low, sizeof(u32));
			memcpy(SAMPLE_DOUBLE + 4, &high, sizeof(u32));

        default:
        	xil_printf("Msg not supported yet...\r\n");
        	break;
        }

	}

	/* close connection */
	close(newsockfd);
	vTaskDelete(NULL);
}


