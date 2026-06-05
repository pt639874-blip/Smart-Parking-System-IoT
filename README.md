# Smart Automatic Parking System 🚗

## Overview
This project is an IoT based Smart Automatic Parking System using Arduino.

## Features
- Automatic gate control
- Ultrasonic vehicle detection
- IR based exit detection
- OLED display slot counter
- Red/Green parking indicators

## Components Used
- Arduino Uno
- Ultrasonic Sensor HC-SR04
- IR Sensor
- Servo Motor
- OLED Display SSD1306
- LEDs

## Connections

Ultrasonic:
- TRIG -> Pin 6
- ECHO -> Pin 7

IR Sensor:
- OUT -> Pin 3

Servo:
- Signal -> Pin 9

OLED:
- SDA -> A4
- SCL -> A5

LEDs:
- Green -> Pin 10
- Red -> Pin 11

## Working

Vehicle Entry:
- Ultrasonic detects vehicle
- Gate opens
- Slot count decreases

Vehicle Exit:
- IR detects exit
- Gate opens
- Slot count increases

## Author

Prajwal Tiwari
