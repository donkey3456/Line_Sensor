# Line_Sensor
line sensor program for robocon 2016

According to my test(line_sensorPD), if the speed is less than 1m/s. The robot car could trace the white line to the top of the slope.
If the speed is faster, the robot car may rush out of the slope.

Currently, the simplest method to improve the performance I think is to use a faster controller. 
If the state of the sensor changed(10degree) every 10ms, the servo motor may not be able to follow the controller. 
Thus I think the performance of the system could reach maximum if each loop costs only 10ms. (currently each loop cost about 30ms)
