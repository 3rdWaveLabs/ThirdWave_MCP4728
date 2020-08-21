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

void setup() {
    dac.begin();
}

void loop() {
    for (int level = 0; level <= 4095; level++) {
        for (int channel = 0; channel < 8; channel ++) {
            dac.setVoltage(channel, level);
        }
    }
    for (int level = 4095; level >= 0; level--) {
        for (int channel = 0; channel < 8; channel ++) {
            dac.setVoltage(channel, level);
        }
    }
}