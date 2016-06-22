/*
 * I2CDev.h  Created on: 22 June 2016
 * Chengtao Wang
 * This Program is changed from the source of Derek Molloy
 */

#ifndef I2C_H_
#define I2C_H_

#define RPI_I2C_1 "/dev/i2c-1"

namespace RPII2C {

/**
 * class I2CDev
 * Generic I2C Device class for any type of I2C device
 */
class I2CDev{
private:
	unsigned int bus;
	unsigned int device;
	int file;
public:
	I2CDev(unsigned int bus, unsigned int device);
	virtual int open();
	virtual int write(unsigned char value);
	virtual unsigned char readRegister(unsigned int registerAddress);
	virtual unsigned char* readRegisters(unsigned int number, unsigned int fromAddress=0);
	virtual int writeRegister(unsigned int registerAddress, unsigned char value);
	virtual void debugDumpRegisters(unsigned int number = 0xff);
	virtual void close();
	virtual ~I2CDevice();
};

} /* namespace RPII2C */

#endif /* I2C_H_ */
