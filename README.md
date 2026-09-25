# light-follower-robot-with-obstacle-avoidance

This project is use three LDR sensors to detect and follow a light source. When an obstacle is detected, the robot uses an HC-SR04 ultrasonic sensor mounted on a servo motor to check the left and right sides, chooses the cleaner direction, move around the obstacle, and then continues following the light.

A push button is used for start-stop control, and a LED to show when the robot is on.

Note: A separate 5V regulator (such as a buck converter) could be used for the servo, but the L298N 5V output is sufficient for this single servo project and keeps the circuit simple.


## Components List

- **1×** Arduino Uno board
- **1×** L298N motor driver module
- **2×** 12v DC gear motor with wheels
- **1×** Servo motor SG90
- **1×** Ultrasonic sensor HC-SR04
- **1×** Passive buzzer
- **3×** LDR light sensors
- **3×** 10Kohm Resistors
- **1×** LED
- **1×** 330ohm Resistor
- **1×** push button
- **2×** 18650 Li-ion batteries (3.7v each)
- **1×** 18650 battery holder
- **1×** 2WD robot chasis kit
- **30×** jumber wires


## Source code:
[code.ino](code.ino)


## Circuit schematic: 

[schematic.fzz](schematic.fzz) 

[schematic.png](schematic.png)
