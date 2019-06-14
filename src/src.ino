//----------------------------------------------------
// File:		src.ino
// Version:  	v0.1.2
// Change date:	28.05.2019
// Autor:    	4Source
// Homepage: 	github.com/4Source
//----------------------------------------------------

#include "EEPROM.h"

#define SDA 4
#define SCL 5
EEPROM eeprom (SDA, SCL, _deviceType::M24512, 0xA0, 400000);

uint16_t memoryaddress = 0x0000;
uint8_t data = 0xFF;
uint8_t data16 [] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10};

uint16_t count = 0x0000;

//Overwrite all
void overwrite(uint16_t maxAddr)
{ 
	memoryaddress = 0;
	if(maxAddr > eeprom.getMaxMemAddr() || maxAddr == 0) maxAddr = eeprom.getMaxMemAddr();
	while(memoryaddress <= maxAddr)
	{
		if(memoryaddress % 500 == 0)
		{
			Serial.print(".");
		}
		eeprom.byte_write(memoryaddress, (uint8_t)memoryaddress);
		memoryaddress++;  
	}
	Serial.println();
	Serial.println("Overwrite all Data!");
}
//Read all
void readAll(uint16_t maxAddr)
{ 
	memoryaddress = 0;
	if(maxAddr > eeprom.getMaxMemAddr() || maxAddr == 0) maxAddr = eeprom.getMaxMemAddr();
	while(memoryaddress <= maxAddr)
	{
		Serial.print(memoryaddress); Serial.print(" 0x"); Serial.print(memoryaddress,HEX);
		Serial.print(" 0x"); Serial.println(eeprom.random_address_read(memoryaddress),HEX);
		memoryaddress++;
	}
	Serial.println("Read all Data!");
}

//Write data to address
void writeData()
{ 
	eeprom.byte_write(memoryaddress, data);
	Serial.print("Write Data! "); Serial.print("0x"); Serial.print(memoryaddress,HEX); Serial.print(" "); Serial.print("0x"); Serial.println(data,HEX);
}
//Read data from address
void readData()
{ 
	Serial.print("0x"); Serial.print(memoryaddress,HEX); Serial.print(" ");
	Serial.print("0x"); Serial.println(eeprom.random_address_read(memoryaddress),HEX);
}
//Write data to address
void writeDataPage()
{ 
	eeprom.page_write(memoryaddress, data16, 10);
	Serial.println("Write Data Page!");
}


//Setup
void setup(void) {
	Serial.begin(115200);
	while(!Serial);
	Serial.println();
	Serial.println("Ready!");
	
	//Overwrite all with @data
	// data = 0x99;
	overwrite(0xFFF);
	
	//Read All
	readAll(0xFFF);
	
	//Write Data 
	memoryaddress = 0x0023;
	data = 0x00;
	writeData();
	
	//Read Data 
	memoryaddress = 0x0023;
	readData();
	
	//Page Write
	memoryaddress = 0x0030;
	writeDataPage();
	
	//Read All
	readAll(0x1000);
	
	//Read Data 
	memoryaddress = 0x0000;
	readData();
	
	delay(10000);
	count = 0;
}
//Loop 
void loop()
{ 
	Serial.print(count); Serial.print(" 0x"); Serial.print(count,HEX); Serial.print(" 0x"); Serial.println(eeprom.current_address_read(),HEX);
	// Serial.print(count); Serial.print(" 0b"); Serial.print(count,BIN); Serial.print(" MSB: 0b"); Serial.print(eeprom.msbMemoryaddress(count),BIN); Serial.print(" LSB: 0b"); Serial.println(eeprom.lsbMemoryaddress(count),BIN);
	if(count > eeprom.getMaxMemAddr())
	{
		count = 0x0000;
		delay(10000);
	}
	count++;
	delay(1000);
} 