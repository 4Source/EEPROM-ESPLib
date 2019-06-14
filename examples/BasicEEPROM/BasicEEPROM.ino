//----------------------------------------------------
// File:		BasicEEPROM.ino
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

EEPROM eeprom (SDA, SCL, type, deviceaddress, 400000);

//Write data to address
void writeData(uint16_t memoryaddress, uint8_t data)
{ 
	eeprom.byte_write(memoryaddress, data);
	Serial.print("Write to 0x"); Serial.print(memoryaddress,HEX); 
	Serial.print(" data 0x"); Serial.println(data,HEX);
}
//Read data from address
uint8_t readData(uint16_t memoryaddress)
{ 
	uint8_t data = eeprom.random_address_read(memoryaddress);
	Serial.print("read at 0x"); Serial.print(memoryaddress,HEX);
	Serial.print(" data 0x"); Serial.println(data, HEX);
	return data;
}

//Setup
void setup(void) {
	Serial.begin(115200);
	while(!Serial);
	Serial.println();
	Serial.println("Ready!");
	
	readData(0x0020);
	writeData(0x0020, 0x7F);
	readData(0x0020);
}
//Loop 
void loop()
{ 
	
} 