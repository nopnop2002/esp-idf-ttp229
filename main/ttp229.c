/*********************************** LICENCE **********************************\
| Copyright (c) 2014, A.E. TEC                                                 |
| All rights reserved.                                                         |
|                                                                              |
| Redistribution and use in source and binary forms, with or without           |
| modification, are permitted provided that the following conditions are met:  |
|                                                                              |
| * Redistributions of source code must retain the above copyright notice,     |
|   this list of conditions and the following disclaimer.                      |
| * Redistributions in binary form must reproduce the above copyright notice,  |
|   this list of conditions and the following disclaimer in the documentation  |
|   and/or other materials provided with the distribution.                     |
|                                                                              |
| THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"  |
| AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE    |
| IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE   |
| ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE    |
| LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR          |
| CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF         |
| SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS     |
| INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN      |
| CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)      |
| ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE   |
| POSSIBILITY OF SUCH DAMAGE.                                                  |
\******************************************************************************/
/************************************ USES ************************************\
| This library designed to communicate with the TTP229 chip  from an Arduino   |
|                                                                              |
| It works with a TTP229 (16-Channel Digital Touch Capacitive Switch Sensor)   |
| using the 2-wires serial interface protocol - only 2 arduino pins.           |
\******************************************************************************/
/*********************************** CIRCUIT **********************************\
| General:                                                                     |
|	* TTP229 VCC to pin VCC                                                    |
|	* TTP229 GND to pin GND                                                    |
|	* TTP229 SCL to any pin you choose...                                      |
|	* TTP229 SDO to any pin you choose...                                      |
|                                                                              |
| 16 Buttons Mode (else 8 Buttons Mode):                                       |
|	* TTP229 TP2 to GND via 1 Megohm resistor!                                 |
|	# Must use the ReadKey16, GetKeys16... else use the ReadKey8, GetKeys8...  |
|                                                                              |
| Multi Keys Mode (else Single key Mode):                                      |
|	* TTP229 TP3 to GND via 1 Megohm resistor!                                 |
|	* TTP229 TP4 to GND via 1 Megohm resistor!                                 |
|                                                                              |
| 64Hz Sampling Rate (else 8Hz Sampling Rate):                                 |
|	* TTP229 TP5 to GND via 1 Megohm resistor!                                 |
|                                                                              |
| 2ms Wake Up Rate (else 4ms Wake Up Rate):                                    |
|	* TTP229 TP6 to GND via 1 Megohm resistor!                                 |
|                                                                              |
| 60sec Key On Timeout (else No Key On Timeout):                               |
|	* TTP229 TP7 to GND via 1 Megohm resistor!                                 |
|                                                                              |
| Important:                                                                   |
|	* Must reconnect the TTP229 power so the mode changes will take effect     |
|	* The 1 Megohm resistors already exist on some TTP229 modules              |
\******************************************************************************/
 
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include <driver/gpio.h>

#include "ttp229.h"


void TTP229_Init(TTP229_t * dev, uint8_t sclPin, uint8_t sdoPin)
{
	dev->_sclPin = sclPin;
	dev->_sdoPin = sdoPin;
	
	gpio_reset_pin( dev->_sclPin );
	gpio_set_direction( dev->_sclPin, GPIO_MODE_OUTPUT );

	gpio_reset_pin( dev->_sdoPin );
	gpio_set_direction( dev->_sdoPin, GPIO_MODE_INPUT );
	
	gpio_set_level( dev->_sclPin, HIGH );
}

uint8_t TTP229_ReadKey8(TTP229_t * dev)
{
	TTP229_WaitForTouch(dev);
	TTP229_Key8(dev);
	return dev->_key8;
}
uint8_t TTP229_GetKey8(TTP229_t * dev)
{
	if (TTP229_IsTouch(dev)) TTP229_Key8(dev);
	return dev->_key8;
}
uint8_t TTP229_ReadKeys8(TTP229_t * dev)
{
	TTP229_WaitForTouch(dev);
	TTP229_Keys8(dev);
	return dev->_keys8;
}
uint8_t TTP229_GetKeys8(TTP229_t * dev)
{
	dev->_key8 = 0;
	if (TTP229_IsTouch(dev)) TTP229_Keys8(dev);
	return dev->_keys8;
}
uint8_t TTP229_ReadKey16(TTP229_t * dev)
{
	TTP229_WaitForTouch(dev);
	TTP229_Key16(dev);
	return dev->_key16;
}
uint8_t TTP229_GetKey16(TTP229_t * dev)
{
	dev->_key16 = 0;
	if (TTP229_IsTouch(dev)) TTP229_Key16(dev);
	return dev->_key16;
}
uint16_t TTP229_ReadKeys16(TTP229_t * dev)
{
	TTP229_WaitForTouch(dev);
	TTP229_Keys16(dev);
	return dev->_keys16;
}
uint16_t TTP229_GetKeys16(TTP229_t * dev)
{
	if (TTP229_IsTouch(dev)) TTP229_Keys16(dev);
	return dev->_keys16;
}
void TTP229_Key8(TTP229_t * dev)
{
	dev->_key8 = 0;
	for (uint8_t i = 0; i < 8; i++)
		if (TTP229_GetBit(dev)) dev->_key8 = i + 1;
	delay(2); // Tout
}
void TTP229_Keys8(TTP229_t * dev)
{
	dev->_keys8 = 0;
	for (uint8_t i = 0; i < 8; i++)
		if (TTP229_GetBit(dev)) dev->_keys8 |= 1 << i;
	delay(2); // Tout
}
void TTP229_Key16(TTP229_t * dev)
{
	dev->_key16 = 0;
	for (uint8_t i = 0; i < 16; i++)
		if (TTP229_GetBit(dev)) dev->_key16 = i + 1;
	delay(2); // Tout
}
void TTP229_Keys16(TTP229_t * dev)
{
	dev->_keys16 = 0;
	for (uint8_t i = 0; i < 16; i++)
		if (TTP229_GetBit(dev)) dev->_keys16 |= 1 << i;
	delay(2); // Tout
}

bool TTP229_GetBit(TTP229_t * dev)
{
	//digitalWrite(dev->_sclPin, LOW);
	gpio_set_level(dev->_sclPin, LOW);
	delayMicroseconds(2); // 500KHz
	//bool retVal = !digitalRead(_sdoPin);
	bool retVal = !gpio_get_level(dev->_sdoPin);
	//digitalWrite(dev->_sclPin, HIGH);
	gpio_set_level(dev->_sclPin, HIGH);
	delayMicroseconds(2); // 500KHz
	return retVal;
}

bool TTP229_IsTouch(TTP229_t * dev)
{
	uint16_t timeout = 5000; // 50ms timeout
	//while (digitalRead(dev->_sdoPin)) // DV LOW
	while (gpio_get_level(dev->_sdoPin)) // DV LOW
	{
		if (--timeout == 0) return false;
		delayMicroseconds(10);
	}
	//while (!digitalRead(dev->_sdoPin)) // DV HIGH
	while (!gpio_get_level(dev->_sdoPin)) // DV HIGH
	{
		if (--timeout == 0) return false;
		delayMicroseconds(10);
	}
	delayMicroseconds(10); // Tw
	return true;
}
/*
Don't use this function.
Watchdog triggere occurs.
*/
void TTP229_WaitForTouch(TTP229_t * dev)
{
	//while (digitalRead(dev->_sdoPin)); // DV LOW
	while (gpio_get_level(dev->_sdoPin)); // DV LOW

	//while (!digitalRead(dev->_sdoPin)); // DV HIGH
	while (!gpio_get_level(dev->_sdoPin)); // DV HIGH
	delayMicroseconds(10); // Tw
}
