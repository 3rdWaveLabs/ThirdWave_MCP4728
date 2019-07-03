/*
 ******************************************************************
Copyright 2019 3rd Wave Labs LLC
 * _____         _ __    __                  __       _
  |___ / _ __ __| / / /\ \ \__ ___   _____  / /  __ _| |__  ___
	|_ \| '__/ _` \ \/  \/ / _` \ \ / / _ \/ /  / _` | '_ \/ __|
   ___) | | | (_| |\  /\  / (_| |\ V /  __/ /__| (_| | |_) \__ \
  |____/|_|  \__,_| \/  \/ \__,_| \_/ \___\____/\__,_|_.__/|___/
 ******************************************************************

 Name:		sinewave.ino
 Created:	7/2/2019 3:39PM
 Author:	William Schroeder
*/
#include <Wire.h>
#include <ThirdWave_MCP4728.h>
#include "Lookup_FullSine.h"

ThirdWave_MCP4728 dac;

// Set this value to 9, 8, 7, 6 or 5 to adjust the resolution
#define DAC_RESOLUTION		(9)	

void setup(void) {
	// For ThridWave_MCP4728 A0 the address is 0x60 (default) or 0x61 for A1
	dac.begin();
	pinMode(2, OUTPUT);
	delay(1000);
}

void loop(void) {
    uint16_t i = 0;
	uint16_t sinPoint;
    // Push out the right lookup table, depending on the selected resolution
    #if DAC_RESOLUTION == 5
      	for (i = 0; i < 32; i++) {
			sinPoint = pgm_read_word(&(DACLookup_FullSine_9Bit[i]));
        	dac.setALL(sinPoint);
      	}
    #elif DAC_RESOLUTION == 6
		for (i = 0; i < 64; i++) {
			sinPoint = pgm_read_word(&(DACLookup_FullSine_9Bit[i]));
        	dac.setALL(sinPoint);
		}
    #elif DAC_RESOLUTION == 7
		for (i = 0; i < 128; i++) {
			sinPoint = pgm_read_word(&(DACLookup_FullSine_9Bit[i]));
        	dac.setALL(sinPoint);
		}
    #elif DAC_RESOLUTION == 9
		for (i = 0; i < 512; i++) {
			sinPoint = pgm_read_word(&(DACLookup_FullSine_9Bit[i]));
        	dac.setALL(sinPoint);
		}
    #else    // Use 8-bit data if nothing else is specified
		for (i = 0; i < 256; i++) {
			sinPoint = pgm_read_word(&(DACLookup_FullSine_9Bit[i]));
        	dac.setALL(sinPoint);
		}
    #endif
}