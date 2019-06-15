//----------------------------------------------------
// File:		EEPROM_M24.cpp
// Version:  	v0.1.6
// Change date:	15.06.2019
// Autor:    	4Source
// Homepage: 	github.com/4Source
//----------------------------------------------------
#include "EEPROM_M24.h"

//private
uint8_t EEPROM::creatDeviceaddress(uint16_t memoryaddress)	//M24C08
{
	uint8_t addr = deviceaddress;
	uint16_t mem = memoryaddress;
  
	if(type >= 2 && type < 5)	//M24C04
	{
		if (bitRead(mem, 8) == 1) 
		{
			bitSet(addr, 1);
		}
		else 
		{
			bitClear(addr, 1);
		}
	}
	if(type >= 3 && type < 5)	//M24C08
	{
		if (bitRead(mem, 9) == 1) 
		{
			bitSet(addr, 2);
		}
		else 
		{
			bitClear(addr, 2);
		}
	}  
	if(type >= 4 && type < 5)	//M24C16
	{
		if (bitRead(mem, 10) == 1) 
		{
			bitSet(addr, 3);
		}
		else 
		{
			bitClear(addr, 3);
		}
	}
	
		
	return (addr >> 1);
}
uint8_t EEPROM::msbMemoryaddress(uint16_t memoryaddress)
{
	uint8_t addr = 0x00;
	if (type == 0 || type == 1)
	{
		if (bitRead(memoryaddress, 0) == 1) {bitSet(addr, 0);}
		else 								{bitClear(addr, 0);}
		if (bitRead(memoryaddress, 1) == 1) {bitSet(addr, 1);}
		else 								{bitClear(addr, 1);}
		if (bitRead(memoryaddress, 2) == 1) {bitSet(addr, 2);}
		else 								{bitClear(addr, 2);}
		if (bitRead(memoryaddress, 3) == 1) {bitSet(addr, 3);}
		else 								{bitClear(addr, 3);}
		if (bitRead(memoryaddress, 4) == 1) {bitSet(addr, 4);}
		else 								{bitClear(addr, 4);}
		if (bitRead(memoryaddress, 5) == 1) {bitSet(addr, 5);}
		else 								{bitClear(addr, 5);}
		if (bitRead(memoryaddress, 6) == 1) {bitSet(addr, 6);}
		else 								{bitClear(addr, 6);}
		
		if (type == 1)
		{
			if (bitRead(memoryaddress, 7) == 1) {bitSet(addr, 7);}
			else 								{bitClear(addr, 7);}
		}
	}
	
	
	
	if (type >= 2)
	{
		if (bitRead(memoryaddress, 8) == 1) {bitSet(addr, 0);}
		else 								{bitClear(addr, 0);}
	}
	if (type >= 3)
	{
		if (bitRead(memoryaddress, 9) == 1) {bitSet(addr, 1);}
		else 								{bitClear(addr, 1);}
	}
	if (type >= 4)
	{
		if (bitRead(memoryaddress, 10) == 1) {bitSet(addr, 2);}
		else 								{bitClear(addr, 2);}
	}
	if (type >= 5)
	{
		if (bitRead(memoryaddress, 11) == 1) {bitSet(addr, 3);}
		else 								{bitClear(addr, 3);}
	}
	if (type >= 6)
	{
		if (bitRead(memoryaddress, 12) == 1) {bitSet(addr, 4);}
		else 								{bitClear(addr, 4);}
	}
	if (type >= 7)
	{
		if (bitRead(memoryaddress, 13) == 1) {bitSet(addr, 5);}
		else 								{bitClear(addr, 5);}
	}
	if (type >= 8)
	{
		if (bitRead(memoryaddress, 14) == 1) {bitSet(addr, 6);}
		else 								{bitClear(addr, 6);}
	}
	if (type >= 9)
	{
		if (bitRead(memoryaddress, 15) == 1) {bitSet(addr, 7);}
		else 								{bitClear(addr, 7);}
	}
	return addr;
}
uint8_t EEPROM::lsbMemoryaddress(uint16_t memoryaddress)
{
	uint8_t addr = 0x00;
	
	if (type >= 2)
	{
		if (bitRead(memoryaddress, 0) == 1) {bitSet(addr, 0);}
		else 								{bitClear(addr, 0);}
		if (bitRead(memoryaddress, 1) == 1) {bitSet(addr, 1);}
		else 								{bitClear(addr, 1);}
		if (bitRead(memoryaddress, 2) == 1) {bitSet(addr, 2);}
		else 								{bitClear(addr, 2);}
		if (bitRead(memoryaddress, 3) == 1) {bitSet(addr, 3);}
		else 								{bitClear(addr, 3);}
		if (bitRead(memoryaddress, 4) == 1) {bitSet(addr, 4);}
		else 								{bitClear(addr, 4);}
		if (bitRead(memoryaddress, 5) == 1) {bitSet(addr, 5);}
		else 								{bitClear(addr, 5);}
		if (bitRead(memoryaddress, 6) == 1) {bitSet(addr, 6);}
		else 								{bitClear(addr, 6);}
		if (bitRead(memoryaddress, 7) == 1) {bitSet(addr, 7);}
		else 								{bitClear(addr, 7);}
	}
	return addr;
}

//constructor
EEPROM::EEPROM(uint8_t SDA, uint8_t SCL, enum _deviceType devType, bool e2, bool e1, bool e0)
{
	Wire.begin(SDA, SCL);
    Wire.setClock(400000);
	type = devType;
	setDevAddr(e2,e1,e0);
}
EEPROM::EEPROM(uint8_t SDA, uint8_t SCL, enum _deviceType devType, bool e2, bool e1, bool e0, uint32_t clockFREQ)
{
	Wire.begin(SDA, SCL);
    Wire.setClock(clockFREQ);
	type = devType;
	setDevAddr(e2,e1,e0);
}
EEPROM::EEPROM(uint8_t SDA, uint8_t SCL, enum _deviceType devType, uint8_t address)
{
    Wire.begin(SDA, SCL);
    Wire.setClock(400000);
	type = devType;
	setDevAddr(address);
}
EEPROM::EEPROM(uint8_t SDA, uint8_t SCL, enum _deviceType devType, uint8_t address, uint32_t clockFREQ)
{
    Wire.begin(SDA, SCL);
    Wire.setClock(clockFREQ);
	type = devType;
	setDevAddr(address);
}

//public
uint8_t EEPROM::current_address_read()
{
	// Serial.println("current_address_read");
	
	uint8_t addr = deviceaddress >> 1;
	uint8_t rdata = 0x00;
	
	// Serial.print("deviceaddress "); Serial.println(deviceaddress, HEX);
	// Serial.print("addr "); Serial.println(addr, HEX);
	
    Wire.requestFrom((uint8_t)addr, (size_t)1, true);
	
	while (Wire.available())
	{
		rdata += Wire.read();
	}

	return rdata;
}
uint8_t EEPROM::random_address_read(uint16_t memoryaddress)
{
	// Serial.println("random_address_read");
	
	uint8_t addr = creatDeviceaddress(memoryaddress);
	uint8_t msb = msbMemoryaddress(memoryaddress);
	uint8_t lsb = lsbMemoryaddress(memoryaddress);
	
	uint8_t rdata = 0x00;
	
	// Serial.print("deviceaddress "); Serial.println(deviceaddress, HEX);
	// Serial.print("memoryaddress "); Serial.println(memoryaddress, HEX);
	// Serial.print("addr "); Serial.println(addr, HEX);
	// Serial.print("msb "); Serial.println(msb, HEX);
	// Serial.print("lsb "); Serial.println(lsb, HEX);
	
	if(type >= 5)
	{
		Wire.beginTransmission(addr);
		Wire.write(msb);
		Wire.write(lsb);
		Wire.endTransmission();
		
		Wire.requestFrom((uint8_t)addr, (size_t)1, true);
		while (Wire.available())
		{
			rdata = Wire.read();
		}
	}
	else
	{
		Wire.beginTransmission(addr);
		Wire.write(msb);
		Wire.endTransmission();
		
		Wire.requestFrom((uint8_t)addr, (size_t)1, true);
		while (Wire.available())
		{
			rdata = Wire.read();
		}
	}

	return rdata;
}
/* void EEPROM::sequential_current_read(uint8_t bytes)
{
	Serial.println("sequential_current_read");
	
	uint8_t addr = deviceaddress >> 1;
	
	// Serial.print("deviceaddress "); Serial.println(deviceaddress, HEX);
	// Serial.print("addr "); Serial.println(addr, HEX);
	
	Wire.requestFrom((uint8_t)addr, (size_t)bytes, true);

	while (Wire.available())
	{
		Serial.print("rdata "); Serial.println(Wire.read());
	}
	
	Serial.println();
	delay(5);
}  */
/* void EEPROM::sequential_random_read(uint16_t memoryaddress, uint8_t bytes)
{
	Serial.println("sequential_random_read");
	
	uint8_t addr = creatDeviceaddress(memoryaddress);
	uint8_t msb = msbMemoryaddress(memoryaddress);
	uint8_t lsb = lsbMemoryaddress(memoryaddress);
	if(bytes > getMaxPageSize()) bytes = getMaxPageSize();
	
	// Serial.print("deviceaddress "); Serial.println(deviceaddress, HEX);
	// Serial.print("memoryaddress "); Serial.println(memoryaddress, HEX);
	// Serial.print("addr "); Serial.println(addr, HEX);
	// Serial.print("msb "); Serial.println(msb, HEX);
	// Serial.print("lsb "); Serial.println(lsb, HEX);

	Wire.beginTransmission(addr);
    Wire.write(msb);
	if(type >= 2) {Wire.write(lsb);}
	Wire.endTransmission();
	
	
    Wire.requestFrom((uint8_t)addr, (size_t)bytes, true);

	while (Wire.available())
	{
		Serial.print("rdata "); Serial.println(Wire.read());
	}
	
	Serial.println();
} */
void EEPROM::byte_write(uint16_t memoryaddress, uint8_t data)
{
	// Serial.println("byte_write");  

	uint8_t addr = creatDeviceaddress(memoryaddress);
	uint8_t msb = msbMemoryaddress(memoryaddress);
	uint8_t lsb = lsbMemoryaddress(memoryaddress);

	// Serial.print("deviceaddress "); Serial.println(deviceaddress, HEX);
	// Serial.print("memoryaddress "); Serial.println(memoryaddress, HEX);
	// Serial.print("addr "); Serial.println(addr, HEX);
	// Serial.print("msb "); Serial.println(msb, HEX);
	// Serial.print("lsb "); Serial.println(lsb, HEX);
	// Serial.print("data "); Serial.println(data, HEX);
	if(type >= 5)
	{
		Wire.beginTransmission(addr);
		Wire.write(msb);
		Wire.write(lsb);
		Wire.write(data);
		Wire.endTransmission();
	}
	else
	{
		Wire.beginTransmission(addr);
		Wire.write(msb);
		Wire.write(data);
		Wire.endTransmission();
	}
	
	delay(5);
}
void EEPROM::byte_write(uint16_t memoryaddress, char data)
{
	// Serial.println("byte_write");  

	uint8_t addr = creatDeviceaddress(memoryaddress);
	uint8_t msb = msbMemoryaddress(memoryaddress);
	uint8_t lsb = lsbMemoryaddress(memoryaddress);

	// Serial.print("deviceaddress "); Serial.println(deviceaddress, HEX);
	// Serial.print("memoryaddress "); Serial.println(memoryaddress, HEX);
	// Serial.print("addr "); Serial.println(addr, HEX);
	// Serial.print("msb "); Serial.println(msb, HEX);
	// Serial.print("lsb "); Serial.println(lsb, HEX);
	// Serial.print("data "); Serial.println(data, HEX);
	if(type >= 5)
	{
		Wire.beginTransmission(addr);
		Wire.write(msb);
		Wire.write(lsb);
		Wire.write(data);
		Wire.endTransmission();
	}
	else
	{
		Wire.beginTransmission(addr);
		Wire.write(msb);
		Wire.write(data);
		Wire.endTransmission();
	}
	
	delay(5);
}
void EEPROM::page_write(uint16_t memoryaddress, uint8_t data[], uint8_t bytes)
{
	// Serial.println("page_write");  
	
	uint8_t addr = creatDeviceaddress(memoryaddress);
	uint8_t msb = msbMemoryaddress(memoryaddress);
	uint8_t lsb = lsbMemoryaddress(memoryaddress);
	if(bytes > getMaxPageSize()) bytes = getMaxPageSize();
     
	// Serial.print("deviceaddress "); Serial.println(deviceaddress, HEX);
	// Serial.print("memoryaddress "); Serial.println(memoryaddress, HEX);
	// Serial.print("addr "); Serial.println(addr, HEX);
	// Serial.print("msb "); Serial.println(msb, HEX);
	// Serial.print("lsb "); Serial.println(lsb, HEX);
	// Serial.print("bytes "); Serial.println(bytes);
	// for(int i = 0; i < bytes; i++) { Serial.print("data ["); Serial.print(i); Serial.print("] "); Serial.println(data[i]); }
	
	Wire.beginTransmission(addr);
	Wire.write(msb);
	if(type >= 5) {Wire.write(lsb);}
	
	for(int i = 0; i < bytes; i++)
	{
		Wire.write(data[i]);
	}
	Wire.endTransmission(true);
	
	delay(5);
}
void EEPROM::page_write(uint16_t memoryaddress, char data[], uint8_t bytes)
{
	// Serial.println("page_write");  
	
	uint8_t addr = creatDeviceaddress(memoryaddress);
	uint8_t msb = msbMemoryaddress(memoryaddress);
	uint8_t lsb = lsbMemoryaddress(memoryaddress);
	if(bytes > getMaxPageSize()) bytes = getMaxPageSize();
     
	// Serial.print("deviceaddress "); Serial.println(deviceaddress, HEX);
	// Serial.print("memoryaddress "); Serial.println(memoryaddress, HEX);
	// Serial.print("addr "); Serial.println(addr, HEX);
	// Serial.print("msb "); Serial.println(msb, HEX);
	// Serial.print("lsb "); Serial.println(lsb, HEX);
	// Serial.print("bytes "); Serial.println(bytes);
	// for(int i = 0; i < bytes; i++) { Serial.print("data ["); Serial.print(i); Serial.print("] "); Serial.println(data[i]); }
	
	Wire.beginTransmission(addr);
	Wire.write(msb);
	if(type >= 5) {Wire.write(lsb);}
	
	for(int i = 0; i < bytes; i++)
	{
		Wire.write(data[i]);
	}
	Wire.endTransmission(true);
	
	delay(5);
}
void EEPROM::page_write(uint16_t memoryaddress, uint16_t data)
{
	// Serial.println("page_write");  
	
	uint8_t addr = creatDeviceaddress(memoryaddress);
	uint8_t msb = msbMemoryaddress(memoryaddress);
	uint8_t lsb = lsbMemoryaddress(memoryaddress);
	
	uint8_t byte0 = (uint8_t)data;
	uint8_t byte1 = (uint8_t)(data>>=8);
     
	// Serial.print("deviceaddress "); Serial.println(deviceaddress, HEX);
	// Serial.print("memoryaddress "); Serial.println(memoryaddress, HEX);
	// Serial.print("addr "); Serial.println(addr, HEX);
	// Serial.print("msb "); Serial.println(msb, HEX);
	// Serial.print("lsb "); Serial.println(lsb, HEX);
	
	Wire.beginTransmission(addr);
	Wire.write(msb);
	if(type >= 5) {Wire.write(lsb);}

	Wire.write(byte1);
	Wire.write(byte0);
	
	Wire.endTransmission(true);
	
	delay(5);
}
void EEPROM::page_write(uint16_t memoryaddress, uint32_t data)
{
		// Serial.println("page_write");  
	
	uint8_t addr = creatDeviceaddress(memoryaddress);
	uint8_t msb = msbMemoryaddress(memoryaddress);
	uint8_t lsb = lsbMemoryaddress(memoryaddress);
	
	uint8_t byte0 = (uint8_t)data;
	uint8_t byte1 = (uint8_t)(data>>=8);
	uint8_t byte2 = (uint8_t)(data>>=8);
	uint8_t byte3 = (uint8_t)(data>>=8);
     
	// Serial.print("deviceaddress "); Serial.println(deviceaddress, HEX);
	// Serial.print("memoryaddress "); Serial.println(memoryaddress, HEX);
	// Serial.print("addr "); Serial.println(addr, HEX);
	// Serial.print("msb "); Serial.println(msb, HEX);
	// Serial.print("lsb "); Serial.println(lsb, HEX);
	
	Wire.beginTransmission(addr);
	Wire.write(msb);
	if(type >= 5) {Wire.write(lsb);}

	Wire.write(byte3);
	Wire.write(byte2);
	Wire.write(byte1);
	Wire.write(byte0);
	
	Wire.endTransmission(true);
	
	delay(5);
}

void EEPROM::setDevAddr(bool e2, bool e1, bool e0)
{
	deviceaddress = 0xA0;
	if(e2){bitSet(deviceaddress, 3);}else{bitClear(deviceaddress, 3);}
	if(e1){bitSet(deviceaddress, 2);}else{bitClear(deviceaddress, 2);}
	if(e0){bitSet(deviceaddress, 1);}else{bitClear(deviceaddress, 1);}
}
void EEPROM::setDevAddr(uint8_t address)
{
	deviceaddress = address;
}
uint8_t EEPROM::getDevAddr()
{
	return deviceaddress;
}
uint16_t EEPROM::getMaxMemAddr()
{
	if (type <= 0)
	{
		return 127;
	}
	else if (type <= 1)
	{
		return 255;
	}
	else if (type <= 2)
	{
		return 511;
	}
	else if (type <= 3)
	{
		return 1023;
	}
	else if (type <= 4)
	{
		return 2047;
	}
	else if (type <= 5)
	{
		return 4095;
	}
	else if (type <= 6)
	{
		return 8191;
	}
	else if (type <= 7)
	{
		return 16383;
	}
	else if (type <= 8)
	{
		return 32767;
	}
	else if (type <= 9)
	{
		return 65535;
	}
	else
	{
		return 0;
	}
}
uint8_t EEPROM::getMaxPageSize()
{
	if (type <= 4)	//M24C01, M24C02, M24C04, M24C08, M24C16
	{
		return 16;
	}
	else if (type <= 6)	//M24C32, M24C64
	{
		return 32;
	}
	else if (type <= 8)	//M24128, M24256
	{
		return 64;
	}
	else if (type <= 9)	//M24512
	{
		return 128;
	}
	else
	{
		return 0;
	}
}
