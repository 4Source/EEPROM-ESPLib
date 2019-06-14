//----------------------------------------------------
// File:		ReadAllEEPROM.ino
// Version:  	v0.1.4
// Change date:	14.06.2019
// Autor:    	4Source
// Homepage: 	github.com/4Source
//----------------------------------------------------

#include <EEPROM_M24.h>

#define SDA 4
#define SCL 5

uint8_t deviceaddress = 0xA0;
enum _deviceType type = _deviceType::M24512;

EEPROM eeprom (SDA, SCL, type, deviceaddress, 1000000);

//Read all
void readAll(uint16_t maxAddr)
{ 
	uint16_t memoryaddress = 0x0000;
	Serial.println(maxAddr);
	if(maxAddr > eeprom.getMaxMemAddr() || maxAddr == 0) maxAddr = eeprom.getMaxMemAddr();
	Serial.println(maxAddr);
	Serial.println(eeprom.getMaxMemAddr());
	
	while(memoryaddress < maxAddr)
	{
		Serial.print(memoryaddress); Serial.print(" 0x"); Serial.print(memoryaddress,HEX);
		Serial.print(" 0x"); Serial.println(eeprom.random_address_read(memoryaddress),HEX);
		memoryaddress++;
	}
	Serial.println("Read all Data!");
}

//Setup
void setup(void) {
	Serial.begin(115200);
	while(!Serial);
	Serial.println();
	Serial.println("Ready!");
	
	//Read all
	readAll(0);
}
//Loop 
void loop()
{ 
	
} 