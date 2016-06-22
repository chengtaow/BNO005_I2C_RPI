/*
 * I2CTest.cpp  Created on: 22 June 2016
 * This program used to test the I2C general class
 * Use the BNO005 sensor.
 * Chengtao Wang
 */

#include <iostream>
#include <unistd.h>
#include "I2CDev.h"

using namespace std;
using namespace RPII2C;

int main{
//The address of BNO005 is 0x28
	I2CDev sensor(1, 0x28);
	sensor.open();
//Read the device number
	char Device = sensor.readRegister(0x00);
//Set the operation mode
	sensor.writeRegister(0x3D, 0x1C);
	
//Now read 6 data from 0x08
//These data will be Acceleration Data X <7:0>, X <15:8>, Y <7:0>, Y <15:8>,Z <7:0>, Z <15:8>.
	char* data = sensor.readMultiRegister(6, 0x08);
//Close connection
	sensor.close();
	
//Now print the results
	cout << 'The default device value of BNO005 is: ' << Device << '\n';
	cout << 'We get six Acceleration Data: ' <<  data << '\n';
	
}

