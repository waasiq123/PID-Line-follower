# PID-Line-follower
A high-speed ESP32-based robot that follows a predefined track using PID control and the SmartElex RLS-08 sensor array. Built with L298N motor drivers and a lightweight chassis, it's optimized for precision and stability.

This repository contains all the code, circuit diagrams, and resources for my **ESP32-based line follower bot** using **PID control** for efficient and precise line tracking.  

Features :
- **ESP32 + SmartElex RLS-08 Sensor Array** for accurate line detection  
- **Dual-motor setup with L298N motor driver**  
- **Optimized PID control for smooth movement**  
- **Lightweight 3D-printed chassis for speed and stability**  

REQUIREMENTS:
- ESP32 (Microcontroller)
- SmartElex RLS-08 (Analog & Digital Line Sensor Array)
- L298N Motor Driver
- 2x Motors (N20 12V 600 RPM)
- 44mm Wheels
- 3x 3.7V Lithium-ion Batteries (for power)
- Battery Holder & Switch
- 3D-printed Chassis (or custom-built frame)
- Wires & Connectors

Code Explanation :
This program controls a line follower robot using an ESP32, an L298N motor driver, and a QTR-8A sensor array. The robot follows a line using PID (Proportional-Integral-Derivative) control to adjust motor speeds dynamically.

Component	Function:
QTR-8A Sensor 	      -    Reads black/white values to detect the track.
PID Algorithm 	      -    Adjusts motor speeds based on deviation from center.
ESP32	                -    Processes data and controls motors.
L298N Motor Driver	  -    Drives the left and right motors.

PID Values:
Kp (Proportional Gain): 0.045
Ki (Integral Gain): 0.005
Kd (Derivative Gain): 0.8
These values determine how the bot corrects its path:

Kp (0.045): Controls immediate response to errors. A higher value makes corrections faster but can cause oscillations.

Ki (0.005): Helps eliminate small errors over time. A low value prevents excessive correction buildup.

Kd (0.8): Reduces overshooting by considering the rate of change of error. A high value smooths movements but may slow responses.
If tuning is needed, try adjusting Kp for faster response, Kd to reduce overshooting, and Ki only if you see steady-state drift.
