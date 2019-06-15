//----------------------------------------------------
// File:		EEPROM_M24.h
// Version:  	v0.1.6
// Change date:	15.06.2019
// Autor:    	4Source
// Homepage: 	github.com/4Source
//----------------------------------------------------
#ifndef EEPROM_M24_h
#define EEPROM_M24_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#endif

#include <Wire.h>

enum _deviceType
	{
		M24C01,		//0		//Not Tested
		M24C02,		//1
		M24C04,		//2
		M24C08,		//3
		M24C16,		//4
		M24C32,		//5		//Not Tested
		M24C64,		//6
		M24128,		//7		//Not Tested
		M24256,		//8
		M24512		//9
	};
	
class EEPROM
{	
	private:
	uint8_t deviceaddress;
	enum _deviceType type;
	
	uint8_t creatDeviceaddress(uint16_t);
	uint8_t msbMemoryaddress(uint16_t);
	uint8_t lsbMemoryaddress(uint16_t);
	
	
	void setDevAddr(bool, bool, bool);
	void setDevAddr(uint8_t);
	
	public:	
	EEPROM(uint8_t, uint8_t, enum _deviceType, bool, bool, bool);
	EEPROM(uint8_t, uint8_t, enum _deviceType, bool, bool, bool, uint32_t);
	EEPROM(uint8_t, uint8_t, enum _deviceType, uint8_t);
	EEPROM(uint8_t, uint8_t, enum _deviceType, uint8_t, uint32_t);
	
	uint8_t current_address_read();
	uint8_t random_address_read(uint16_t);
	// void sequential_current_read(uint8_t);
	// void sequential_random_read(uint16_t, uint8_t);
	void byte_write(uint16_t, uint8_t);
	void byte_write(uint16_t, char);
	void page_write(uint16_t, uint8_t[], uint8_t);
	void page_write(uint16_t, char[], uint8_t);
	void page_write(uint16_t, uint16_t);
	void page_write(uint16_t, uint32_t);
	
	uint8_t getDevAddr();
	uint16_t getMaxMemAddr();
	uint8_t getMaxPageSize();

};
#endif
//deviceaddress:
//		   		7 6 5 4  3   2   1  0
// M24C01: 		1 0 1 0 E2   E1  E0 RW		 128 byte	Nr. 0
// M24C02: 		1 0 1 0 E2   E1  E0 RW		 256 byte	Nr. 1
// M24C04: 		1 0 1 0 E2   E1  A8 RW		 512 byte	Nr. 2
// M24C08: 		1 0 1 0 E2   A9  A8 RW		1024 byte	Nr. 3
// M24C16: 		1 0 1 0 A10  A9  A8 RW		2048 byte	Nr. 4
// M24C32: 		1 0 1 0 E2   E1  E0 RW		4096 byte	Nr. 5
// M24C32-D:	1 0 1 1 E2   E1  E0 RW		  32 byte
// M24C64:		1 0 1 0 E2   E1  E0 RW		8192 byte	Nr. 6
// M24C64-D:	1 0 1 1 E2   E1  E0 RW		  32 byte
// M24128:		1 0 1 0 E2   E1  E0 RW	   16384 byte	Nr. 7
// M24128-D:	1 0 1 1 E2   E1  E0 RW		  64 byte
// M24256:		1 0 1 0 E2   E1  E0 RW	   32768 byte	Nr. 8
// M24256-D:	1 0 1 1 E2   E1  E0 RW		  64 byte
// M24512:		1 0 1 0 E2   E1  E0 RW	   65536 byte	Nr. 9
// M24512-D:	1 0 1 1 E2   E1  E0 RW		 128 byte


//memoryaddress:
// MSB7  MSB6  MSB5  MSB4  MSB3  MSB2  MSB1  MSB0
//  A15   A14   A13   A12   A11   A10    A9    A8
//65536 32768 16384  8192  4096  2048  1024   512

// LSB7  LSB6  LSB5  LSB4  LSB3  LSB2  LSB1  LSB0
//   A7    A6    A5    A4    A3    A2    A1    A0
//  256   128    64    32    16     8     4     2