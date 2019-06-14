//----------------------------------------------------
// File:		OverwriteEEPROM.ino
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

//Overwrite all
void overwrite(uint16_t maxAddr, uint8_t data)
{ 
	uint16_t memoryaddress = 0x0000;
	if(maxAddr > eeprom.getMaxMemAddr() || maxAddr == 0) maxAddr = eeprom.getMaxMemAddr();
	Serial.print("Overwrite "); Serial.print(maxAddr); Serial.print(" addresses with 0x"); Serial.println(data, HEX);
	while(memoryaddress < maxAddr)
	{
		if(memoryaddress % (maxAddr/10) == 0)
		{
			Serial.print(".");
		}
		eeprom.byte_write(memoryaddress, data);
		memoryaddress++;  
	}
	Serial.println("100%");
	Serial.println("Overwrite all Data!");
}

//Setup
void setup(void) {
	Serial.begin(115200);
	while(!Serial);
	Serial.println();
	Serial.println("Ready!");
	
	//Overwrite all with 0xFF
	overwrite(0, 0xFF);
}
//Loop 
void loop()
{ 
	
} 