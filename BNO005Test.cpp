/*
 * BNO005Test.cpp  Created on: 23 June 2016
 * Chengtao Wang
 * This program is the test program for BNO005 class
 */

#include <unistd.h>
#include <iostream>
#include "BNO005.h"

using namespace std;
using namespace RPII2C;

int main(){
	BNO005 sensor(1);
	sensor.getMagnetometer();
	return 0;
}