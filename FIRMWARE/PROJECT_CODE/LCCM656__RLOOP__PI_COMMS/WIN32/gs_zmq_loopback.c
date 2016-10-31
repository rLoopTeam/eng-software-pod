#include "gs_zmq_loopback.h"
#include "zmq.h"
#include <stdint.h>
#include<stdio.h>
#include<winsock2.h>
#include <Windows.h>

#pragma comment(lib,"ws2_32.lib") //Winsock Library

#define SERVER "239.3.14.159"  //ip address of udp server
#define BUFLEN 512  //Max length of buffer
#define PORT 50051   //The port on which to listen for incoming data

//ZMQ stuff
void *context;
void *pubTelemetry;
int rc;
char nodeName[100];

void CALLBACK doUDPBroadcast(PVOID lpParameter, BOOLEAN TimerOrWaitFired);

//Starts broadcasting network beacon and initializes ZMQ context
void InitGSLoopback(char *_nodeName)
{
	if (strlen(_nodeName) < 100)
		memcpy(&nodeName, _nodeName, strlen(_nodeName));

	//Get the ZMQ Pub socket all setup

	//Create a context
	context = zmq_ctx_new();

	//Assign a publisher socket to our context
	pubTelemetry = zmq_socket(context, ZMQ_PUB);

	//Attch the publisher socket to a tcp port
	rc = zmq_bind(pubTelemetry, "tcp://*:3000");

	//Create a periodic timer announcing the publisher socket to the ground station
	HANDLE hNewTimer = NULL;                                                                                                                        //call after
	BOOL IsCreated = CreateTimerQueueTimer(&hNewTimer, NULL, doUDPBroadcast, NULL, 1000,
		// repeat
		1000, WT_EXECUTELONGFUNCTION);

	/* This code could go in a deconstructor
	zmq_close(pubTelemetry);
	zmq_ctx_destroy(context);
	*/
}

//Pushes the data out the zmq pub socket to the ground station
void SendGSMessage(uint8_t *buf, uint16_t bufLen)
{
	//Verify the context started up ok
	if (rc != 0)
		return;

	uint8_t ZMQTxBuffer[RPOD_I2C_BUFFER_SIZE];

	//Pack the new data packet into the ZMQ transmit buffer
	//along with some metadata at the start and send it out
	if ((bufLen + strlen(nodeName) + strlen(nodeName)) < RPOD_I2C_BUFFER_SIZE) {
		char * t = "telemetry ";
		memcpy(&ZMQTxBuffer, t, strlen(t));
		memcpy(ZMQTxBuffer + strlen(t), &nodeName, strlen(nodeName));
		memcpy(ZMQTxBuffer + strlen(t) + strlen(nodeName), buf, bufLen + strlen(t) + strlen(nodeName));
		zmq_send(pubTelemetry, ZMQTxBuffer, bufLen + strlen(t) + strlen(nodeName), 0);
	}
	else {
		printf("ZMQ TX buffer too small.\n");
	}
}

void CALLBACK doUDPBroadcast(PVOID lpParameter, BOOLEAN TimerOrWaitFired)
{
	struct sockaddr_in si_other;
	int s, slen = sizeof(si_other);
	char buf[BUFLEN];
	const char* preamble = "rPod! ";
	char message[50];
	WSADATA wsa;

	
	memcpy(&message, preamble, strlen(preamble)+1);
	memcpy(message + strlen(message), &nodeName, strlen(nodeName)+1);

	//Initialise winsock
	printf("\nInitialising Winsock...");
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		printf("Failed. Error Code : %d", WSAGetLastError());
		exit(EXIT_FAILURE);
	}
	printf("Initialised.\n");

	//create socket
	if ((s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == SOCKET_ERROR)
	{
		printf("socket() failed with error code : %d", WSAGetLastError());
		exit(EXIT_FAILURE);
	}

	//setup address structure
	memset((char *)&si_other, 0, sizeof(si_other));
	si_other.sin_family = AF_INET;
	si_other.sin_port = htons(PORT);
	si_other.sin_addr.S_un.S_addr = inet_addr(SERVER);

	//send the message
	if (sendto(s, message, strlen(message), 0, (struct sockaddr *) &si_other, slen) == SOCKET_ERROR)
	{
		printf("sendto() failed with error code : %d", WSAGetLastError());
		exit(EXIT_FAILURE);
	}

	closesocket(s);
	WSACleanup();
}