/*
 * BNO005.h  Created on: 22 June 2016
 * Chengtao Wang
 * This program provides the I2C library for the communication between BNO005 and Raspberry Pi 2
 */

#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include "BNO005.h"

using namespace std;

namespace RPII2C{

//From the data sheet
#define CHIPID			0x00

// Accelaration data register
#define ACCXLSB			0x08
#define ACCXMSB			0x09
#define ACCYLSB			0x0A
#define ACCYMSB			0x0B
#define ACCZLSB			0x0C
#define ACCZMSB			0x0D

//Magnetometer data register
#define MAGXLSB			0x0E
#define MAGXMSB			0x0F
#define MAGYLSB			0x10
#define MAGYMSB			0x11
#define MAGZLSB			0x12
#define MAGZMSB			0x13

//Gyroscope data register
#define GYROXLSB		0x14
#define GYROXMSB		0x15
#define GYROYLSB		0x16
#define GYROYMSB		0x17
#define GYROZLSB		0x18
#define GYROZMSB		0x19

//Temperature data register
#define TEMP			0x34

//Mode register
#define OPRMODE			0x3D
#define PWRMODE			0x3E
#define SYSTRIGGER		0x3F
#define TEMPSOURCE		0x40

short BNO005::combineRegister(unsigned char msb, unsigned char lsb){
	return ((short)msb<<8)|(short)lsb;
}

//The constructor for the BNO005 subclass
BNO005::BNO005(unsigned int I2CBus, unsigned int I2CAddress):
	I2CDev(I2CBus, I2CAddress){
	//Calls the parent constructor
	this->I2CBus = I2CBus;
	this->I2CAddress = I2CAddress;
	this->Acceleration = NULL;
	//this->Magnetometer = NULL;
	//this->Gyroscope = NULL;
	this->writeValue(OPRMODE,0x1C);
}

void BNO005::getMagnetometer(){
	unsigned char *magvalue = this->readMultiRegister(6, MAGXLSB);
	double *magdata;
	//1uT = 16 LSB
	magdata[0] = (double)this->combineRegister(magvalue[1], magvalue[0])/16.0;
	magdata[1] = (double)this->combineRegister(magvalue[3], magvalue[2])/16.0;
	magdata[2] = (double)this->combineRegister(magvalue[5], magvalue[4])/16.0;
	this->Acceleration = magdata;
	cout << "The Magnetometer value of BNO005 in X direction is: " << Acceleration[0] << '\n';
	cout << "The Magnetometer value of BNO005 in Y direction is: " << Acceleration[1] << '\n';
	cout << "The Magnetometer value of BNO005 in Z direction is: " << Acceleration[2] << '\n';
}



BNO005::~BNO005() {}

} // namespace RPII2C
