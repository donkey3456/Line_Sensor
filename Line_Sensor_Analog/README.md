Thanks to DavidNg, we now have the posibility to estimate the accurate position of the white line. With accurate position, we could use PID control to control the robot.

Currently the old program could not work with the new board. we need to find out the problem. 

On the other hand, we need to write a new program.

Following is my plan. Any advice is welcome.
First, write a simple debug program which could print anolog input of each sensor.
we then try to adjust them to the same value if the sensors are detecting the same content.

then we write the program for line tracking.

1. find 3 smallest values of the 8 sensors. 
2. Average those values, and take the result as the background.
3. minus the background, and find the center of the white line.



Circuit for each sensor channel:

![circuit](https://cloud.githubusercontent.com/assets/14858968/12377366/6f6cb8ca-bd56-11e5-8371-3b16cc7906b7.jpg)
