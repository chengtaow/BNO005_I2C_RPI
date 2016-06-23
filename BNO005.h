/*
 * BNO005.h  Created on: 22 June 2016
 * Chengtao Wang
 * This program provides the I2C library for the communication between BNO005 and Raspberry Pi 2
 */

#ifndef BNO005_H_
#define BNO005_H_
#include "I2CDev.h"

// The BNO005 has 0x7F registers (Some of them are reserved)
#define BUFFER_SIZE 0x7F

namespace RPII2C{

class BNO005:protected I2CDev{

private:
	unsigned int I2CBus, I2CAddress;
	//unsigned char *registers;
	double *Acceleration;
	//double* Magnetometer;
	//double* Gyroscope;
	short combineRegister(unsigned char msb, unsigned char lsb);
	
public:
	BNO005(unsigned int I2CBus, unsigned int I2CAddress=0x28);
	//virtual double *getAcceleration();
	virtual void getMagnetometer();
	//virtual double *getGyroscope();

	virtual ~BNO005();
	
};

}  /* namespace RPII2C */

#endif /* BNO005_H_ */
