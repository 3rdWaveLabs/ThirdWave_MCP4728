/*
 ******************************************************************
Copyright 2019 3rd Wave Labs LLC
 * _____         _ __    __                  __       _
  |___ / _ __ __| / / /\ \ \__ ___   _____  / /  __ _| |__  ___
	|_ \| '__/ _` \ \/  \/ / _` \ \ / / _ \/ /  / _` | '_ \/ __|
   ___) | | | (_| |\  /\  / (_| |\ V /  __/ /__| (_| | |_) \__ \
  |____/|_|  \__,_| \/  \/ \__,_| \_/ \___\____/\__,_|_.__/|___/
 ******************************************************************

 Name:		trianglewave.ino
 Created:	7/2/2019 2:16PM
 Author:	William Schroeder
*/
#include <Wire.h>
#include <ThirdWave_MCP4728.h>

ThirdWave_MCP4728 dac;

void setup(void) {
	/// For ThridWave_MCP4728 A0 the address is 0x60 (default) or 0x61 for A1
	dac.begin();
}

void loop(void) {
    uint32_t counter;
    // Run through the full 12-bit scale for a triangle wave
	counter = 0;
    while(counter < 4096) {
		dac.setAll(counter);
		counter++;
    }
    while(counter > 0) {
		dac.setAll(counter);
		counter--;
    }
	 
}