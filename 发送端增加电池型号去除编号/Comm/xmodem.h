#ifndef __XMODEM_H
#define __XMODEM_H

/* ---------------------------------------------- */

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned long uint32_t;
typedef signed char int8_t;
typedef signed short int16_t;
typedef signed long int32_t;

typedef struct{
	uint8_t header;		// Start Of Header   
	uint8_t packetNum;	// Packet Number
	uint8_t _pakcetNum; // ~(Packet Number)
	uint8_t data[128];	// Packet Data
	uint8_t check;		// 16Bit CRC 
}XModemData_t;


/* XModem control character */
#define XMODEM_SOH 0x01
#define XMODEM_EOT 0x04
#define XMODEM_ACK 0x06
#define XMODEM_CAN 0x18
#define XMODEM_NAK 0x15

extern uint8_t XModemSeq[132];

void XModemSend(bool success);
void XModemSend();
void XModemRecv();
BOOL XModemStop();
BOOL XModemStart();
#endif //__XMODEM_H