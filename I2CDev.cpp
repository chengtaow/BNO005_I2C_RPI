/*
 * I2CDev.cpp  Created on: 22 June 2016
 * Chengtao Wang
 * This Program is changed from the source of Derek Molloy
 */

#include <iostream>
#include <sstream>
#include <fcntl.h>
#include <stdio.h>
#include <iomanip>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include "I2CDev.h"

using namespace std;

#define HEX(x) setw(2) << setfill('0') << hex << (int)(x)

namespace RPII2C {

/**
 * Constructor for the I2CDev class.
 * Parameter bus: The bus number.
 * Parameter device: The device ID on the bus.
 */
I2CDev::I2CDev(unsigned int bus, unsigned int device) {
	this->file=-1;
	this->bus = bus;
	this->device = device;
	this->open();
}

/**
 * Open a connection to an I2C device
 * return 1 on failure to open to the bus or device, 0 on success.
 */
int I2CDev::open(){
	string name;
	if(this->bus == 1) name = RPI_I2C_1;

	if((this->file=::open(name.c_str(), O_RDWR)) < 0){
		perror("I2C: failed to open the bus\n");
		return 1;
	}
	if(ioctl(this->file, I2C_SLAVE, this->device) < 0){
		perror("I2C: Failed to connect to the device\n");
		return 1;
	}
	return 0;
}

/**
 * Write a single byte value to a single register.
 * Parameter registerAddress: The register address
 * Parameter value: The value to be written to the register
 * Return 1 on failure to write, 0 on success.
 */

int I2CDev::writeRegister(unsigned int registerAddress, unsigned char value){
	unsigned char buffer[2];
	buffer[0] = registerAddress;
	buffer[1] = value;
	if(::write(this->file, buffer, 2)!=2){
		perror("I2C: Failed write to the device\n");
		return 1;
	}
	return 0;
}

/**
 * Write a single value to the I2C device. Used to set up the device to read from a
 * particular address.
 * Parameter value: the value to write to the device
 * Return 1 on failure to write, 0 on success.
 */
int I2CDev::writeValue(unsigned char value){
	unsigned char buffer[1];
	buffer[0]=value;
	if (::write(this->file, buffer, 1)!=1){
		perror("I2C: Failed to write to the device\n");
		return 1;
	}
	return 0;
}

/**
 * Read a single register value from the address on the device.
 * Parameter registerAddress: the address to read from
 * Return the byte value at the register address.
 */
unsigned char I2CDev::readRegister(unsigned int registerAddress){
	this->writeValue(registerAddress);
	unsigned char buffer[1];
	if(::read(this->file, buffer, 1)!=1){
		perror("I2C: Failed to read in the value.\n");
		return 1;
	}
	return buffer[0];
}

/**
 * Method to read a number of registers from a single device. This is much more efficient than
 * reading the registers individually. The from address is the starting address to read from, which
 * defaults to 0x00.
 * Parameter number: the number of registers to read from the device
 * Parameter fromAddress: the starting address to read from
 * Return a pointer of type unsigned char* that points to the first element in the block of registers
 */
unsigned char* I2CDev::readMultiRegister(unsigned int number, unsigned int fromAddress){
	this->writeValue(fromAddress);
	unsigned char* data = new unsigned char[number];
	if(::read(this->file, data, number)!=(int)number){
		perror("IC2: Failed to read in the full buffer.\n");
		return NULL;
	}
	return data;
}

/**
 * Method to dump the registers to the standard output. It inserts a return character after every
 * 16 values and displays the results in hexadecimal to give a standard output using the HEX() macro
 * that is defined at the top of this file. The standard output will stay in hexadecimal format, hence
 * the call on the last like.
 * Parameter number: the total number of registers to dump, defaults to 0xff
 */

void I2CDev::debugDumpRegisters(unsigned int number){
	cout << "Dumping Registers for Debug Purposes:" << endl;
	unsigned char *registers = this->readMultiRegister(number);
	for(int i=0; i<(int)number; i++){
		cout << HEX(*(registers+i)) << " ";
		if (i%16==15) cout << endl;
	}
	cout << dec;
}

/**
 * Close the file handlers and sets a temporary state to -1.
 */
void I2CDev::close(){
	::close(this->file);
	this->file = -1;
}

/**
 * Closes the file on destruction, provided that it has not already been closed.
 */
I2CDev::~I2CDev() {
	if(file!=-1) this->close();
}

} /* namespace RPII2C */
