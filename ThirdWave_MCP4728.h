/*
 ******************************************************************
Copyright 2019 3rd Wave Labs LLC
 * _____         _ __    __                  __       _
  |___ / _ __ __| / / /\ \ \__ ___   _____  / /  __ _| |__  ___
	|_ \| '__/ _` \ \/  \/ / _` \ \ / / _ \/ /  / _` | '_ \/ __|
   ___) | | | (_| |\  /\  / (_| |\ V /  __/ /__| (_| | |_) \__ \
  |____/|_|  \__,_| \/  \/ \__,_| \_/ \___\____/\__,_|_.__/|___/
 ******************************************************************

 Name:		ThirdWave_MCP4728.h
 Created:	7/2/2019 9:48AM
 Author:	William Schroeder
*/
#include "Arduino.h"
#include <Wire.h>

#define MCP4728_A0						(0x60)
#define MCP4728_A1						(0x61)
#define MCP4728_CMD_WRITEDAC            (0x40)  // Normal writes data to the DAC

class ThirdWave_MCP4728 {
private:
	uint8_t _i2caddr;
	uint8_t twbrback;
	void setFastI2CFrequency();
	void restoreI2CFrequency();
public:
	ThirdWave_MCP4728() {}
	void begin();  
	void setVoltage(uint8_t channel, uint16_t output);
	void setAll(uint16_t output);
	void setAll(uint16_t output0, uint16_t output1, uint16_t output2, uint16_t output3, uint16_t output4, uint16_t output5, uint16_t output6, uint16_t output7);
};

void ThirdWave_MCP4728::setFastI2CFrequency() {
	#ifdef TWBR
		twbrback = TWBR;
		TWBR = ((F_CPU / 400000L) - 16) / 2; // Set I2C frequency to 400kHz
	#endif
}

void ThirdWave_MCP4728::restoreI2CFrequency() {
	#ifdef TWBR
		TWBR = twbrback;
	#endif
}

void ThirdWave_MCP4728::begin() {
	Wire.begin();
	this->setAll(0);
}

/* setVoltage: sets the 'channel' to the value of 'output'
*	channel: values 0 - 7
*	output: values 0 - 4095 */
void ThirdWave_MCP4728::setVoltage(uint8_t channel, uint16_t output) {
	if (channel > 7 || channel < 0) return;
	setFastI2CFrequency();

	if (channel < 4) _i2caddr = MCP4728_A0; // Use DAC0
	else {
		_i2caddr = MCP4728_A1; // Use DAC1
		channel -= 4; //each dac only accepts 0 - 3 so for example an input of 6 means DAC1 ch 2
	}

	Wire.beginTransmission(_i2caddr);
	Wire.write(MCP4728_CMD_WRITEDAC | (channel << 1));	// Configuration bits 		(0		1		0		1		1		DAC1	DAC0	UDAC) 01000000 = 0x40 = MCP4728_CMD_WRITEDAC, DAC1-DAC0 = channel
	Wire.write((output >> 8));							// Upper data bits          (Vref	PD1		PD0		Gain	D11		D10		D9		D8) Vref = 0, PD1-PD0 = 00, Gain = 0 (x1)
	Wire.write(output);									// Lower data bits          (D7		D6		D5		D4		D3		D2		D1		D0)
	Wire.endTransmission();

	restoreI2CFrequency();
}

/* setAll: sets all channels to the same value
*	output: values 0 - 4095 */
void ThirdWave_MCP4728::setAll(uint16_t output) {
	setFastI2CFrequency();

	Wire.beginTransmission(MCP4728_A0);
	//Channel 0
	Wire.write((output >> 8));							// Upper data bits          (0		0		PD1		PD0		D11		D10		D9		D8) 00 = fast write, PD1-PD0 = 00
	Wire.write(output);									// Lower data bits          (D7		D6		D5		D4		D3		D2		D1		D0)
	//Channel 1
	Wire.write((output >> 8));							// Upper data bits          (X		X		PD1		PD0		D11		D10		D9		D8) XX = dont care, PD1-PD0 = 00
	Wire.write(output);									// Lower data bits          (D7		D6		D5		D4		D3		D2		D1		D0)
	//Channel 2
	Wire.write((output >> 8));							// Upper data bits          (X		X		PD1		PD0		D11		D10		D9		D8) XX = dont care, PD1-PD0 = 00
	Wire.write(output);									// Lower data bits          (D7		D6		D5		D4		D3		D2		D1		D0)
	//Channel 3
	Wire.write((output >> 8));							// Upper data bits          (X		X		PD1		PD0		D11		D10		D9		D8) XX = dont care, PD1-PD0 = 00
	Wire.write(output);									// Lower data bits          (D7		D6		D5		D4		D3		D2		D1		D0)
	Wire.endTransmission();

	Wire.beginTransmission(MCP4728_A1);
	//Channel 4
	Wire.write((output >> 8));							// Upper data bits          (0		0		PD1		PD0		D11		D10		D9		D8) 00 = fast write, PD1-PD0 = 00
	Wire.write(output);									// Lower data bits          (D7		D6		D5		D4		D3		D2		D1		D0)
	//Channel 5
	Wire.write((output >> 8));							// Upper data bits          (X		X		PD1		PD0		D11		D10		D9		D8) XX = dont care, PD1-PD0 = 00
	Wire.write(output);									// Lower data bits          (D7		D6		D5		D4		D3		D2		D1		D0)
	//Channel 6
	Wire.write((output >> 8));							// Upper data bits          (X		X		PD1		PD0		D11		D10		D9		D8) XX = dont care, PD1-PD0 = 00
	Wire.write(output);									// Lower data bits          (D7		D6		D5		D4		D3		D2		D1		D0)
	//Channel 7
	Wire.write((output >> 8));							// Upper data bits          (X		X		PD1		PD0		D11		D10		D9		D8) XX = dont care, PD1-PD0 = 00
	Wire.write(output);									// Lower data bits          (D7		D6		D5		D4		D3		D2		D1		D0)
	Wire.endTransmission();

	restoreI2CFrequency();
}

/* setAll: sets each channel to each corresponding value
*	output0 - output7: values 0 - 4095 */
void ThirdWave_MCP4728::setAll(uint16_t output0, uint16_t output1, uint16_t output2, uint16_t output3, uint16_t output4, uint16_t output5, uint16_t output6, uint16_t output7) {
	setFastI2CFrequency();

	Wire.beginTransmission(MCP4728_A0);
	//Channel 0
	Wire.write((output0 >> 8));							// Upper data bits          (0		0		PD1		PD0		D11		D10		D9		D8) 00 = fast write, PD1-PD0 = 00
	Wire.write(output0);								// Lower data bits          (D7		D6		D5		D4		D3		D2		D1		D0)
	//Channel 1
	Wire.write((output1 >> 8));							// Upper data bits          (X		X		PD1		PD0		D11		D10		D9		D8) XX = dont care, PD1-PD0 = 00
	Wire.write(output1);								// Lower data bits          (D7		D6		D5		D4		D3		D2		D1		D0)
	//Channel 2
	Wire.write((output2 >> 8));							// Upper data bits          (X		X		PD1		PD0		D11		D10		D9		D8) XX = dont care, PD1-PD0 = 00
	Wire.write(output2);								// Lower data bits          (D7		D6		D5		D4		D3		D2		D1		D0)
	//Channel 3
	Wire.write((output3 >> 8));							// Upper data bits          (X		X		PD1		PD0		D11		D10		D9		D8) XX = dont care, PD1-PD0 = 00
	Wire.write(output3);								// Lower data bits          (D7		D6		D5		D4		D3		D2		D1		D0)
	Wire.endTransmission();

	Wire.beginTransmission(MCP4728_A1);
	//Channel 4
	Wire.write((output4 >> 8));							// Upper data bits          (0		0		PD1		PD0		D11		D10		D9		D8) 00 = fast write, PD1-PD0 = 00
	Wire.write(output4);								// Lower data bits          (D7		D6		D5		D4		D3		D2		D1		D0)
	//Channel 5
	Wire.write((output5 >> 8));							// Upper data bits          (X		X		PD1		PD0		D11		D10		D9		D8) XX = dont care, PD1-PD0 = 00
	Wire.write(output5);								// Lower data bits          (D7		D6		D5		D4		D3		D2		D1		D0)
	//Channel 6
	Wire.write((output6 >> 8));							// Upper data bits          (X		X		PD1		PD0		D11		D10		D9		D8) XX = dont care, PD1-PD0 = 00
	Wire.write(output6);								// Lower data bits          (D7		D6		D5		D4		D3		D2		D1		D0)
	//Channel 7
	Wire.write((output7 >> 8));							// Upper data bits          (X		X		PD1		PD0		D11		D10		D9		D8) XX = dont care, PD1-PD0 = 00
	Wire.write(output7);								// Lower data bits          (D7		D6		D5		D4		D3		D2		D1		D0)
	Wire.endTransmission();

	restoreI2CFrequency();
}