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

#ifndef TTP229_h
#define TTP229_h

#include "freertos/FreeRTOS.h"

#define HIGH 1
#define LOW  0

#define delayMicroseconds(microsec) esp_rom_delay_us(microsec)
#define delay(millsec) esp_rom_delay_us(millsec*1000)

typedef struct {
	uint8_t _sclPin;
	uint8_t _sdoPin;
	uint8_t _key8;
	uint8_t _keys8;
	uint8_t _key16;
	uint16_t _keys16;
} TTP229_t;

void TTP229_Init(TTP229_t * dev, uint8_t sclPin, uint8_t sdoPin);
uint8_t TTP229_ReadKey8(TTP229_t * dev);
uint8_t TTP229_GetKey8(TTP229_t * dev);
uint8_t TTP229_ReadKeys8(TTP229_t * dev);
uint8_t TTP229_GetKeys8(TTP229_t * dev);
uint8_t TTP229_ReadKey16(TTP229_t * dev);
uint8_t TTP229_GetKey16(TTP229_t * dev);
uint16_t TTP229_ReadKeys16(TTP229_t * dev);
uint16_t TTP229_GetKeys16(TTP229_t * dev);
void TTP229_WaitForTouch(TTP229_t * dev);
void TTP229_Key8(TTP229_t * dev);
void TTP229_Keys8(TTP229_t * dev);
void TTP229_Key16(TTP229_t * dev);
void TTP229_Keys16(TTP229_t * dev);
bool TTP229_IsTouch(TTP229_t * dev);
bool TTP229_GetBit(TTP229_t * dev);
			
#if 0
		uint8_t _sclPin, _sdoPin;
		uint8_t _key8, _keys8, _key16;
		uint16_t _keys16;
#endif


#endif
