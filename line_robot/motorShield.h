/**************************************************************
* Class:  CSC-615-01 Spring 2020
* Team: Tuna Flatcakes
* Name: Marlon Bustamante (917271698)
* Name: 
* Name:
* Name:
* Project: Line Following Robot
*
* File: motorShield.h
*
* Description: 
*
**************************************************************/

/*
* Motor placement
*   ___________
*  /           \
* |             |
* | M1      M2  |
* |             |
* |             |
* |             |
* | M3      M4  |
* |_____________|
* 
*/

#ifndef MOTORSHIELD_H
#define MOTORSHIELD_H

// Using BCM Pinout

// Motor 1
#define MOTOR_1_ENABLE 17  // GPIO 17
#define MOTOR_1_CONTROL 27  // GPIO 27
#define MOTOR_1_CONTROL_2 22 // GPIO 22

// Motor 2
#define MOTOR_2_ENABLE 25 // GPIO 25
#define MOTOR_2_CONTROL 23  // GPIO 23
#define MOTOR_2_CONTROL_2 24  // GPIO 24

// Motor 3
#define MOTOR_3_ENABLE 10 // GPIO 10
#define MOTOR_3_CONTROL 9 // GPIO 9
#define MOTOR_3_CONTROL_2 11 // GPIO 11

// Motor 4
#define MOTOR_4_ENABLE 12 // GPIO 12
#define MOTOR_4_CONTROL 8 // GPIO 8
#define MOTOR_4_CONTROL_2 7 // GPIO 7

void motorSetup();
void stopMotor();
void moveCar(int direction);

#endif