# light-follower-robot-with-obstacle-avoidance

This project is use three LDR sensors to detect and follow a light source. When an obstacle is detected, the robot uses an HC-SR04 ultrasonic sensor mounted on a servo motor to check the left and right sides, chooses the cleaner direction, move around the obstacle, and then continues following the light.

Note: A separate 5V regulator (such as a buck converter) could be used for the servo, but the L298N 5V output is sufficient for this single servo project and keeps the circuit simple.


## Source code:
[code.ino](code.ino)


## Circuit schematic: 

[schematic.fzz](schematic.fzz) 

[schematic.png](schematic.png)
