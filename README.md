#BNO005_I2C_RPI
The I2C class for the raspberry pi 2. Use the sensor BNO005.
To build a test program for the I2CDev class:
```
g++ I2CDev.cpp I2CTest.cpp -o I2Ctest
```

Still working on the BNO005 subclass (BNO005.h BNO005.cpp).

It is said that the Raspberry Pi I2C hardware has a clock stretching issues. There are some errors in the clock signals.I will figure it out later.
