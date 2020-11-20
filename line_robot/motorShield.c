/**************************************************************
* Class:  CSC-615-01 Spring 2020
* Team: Tuna Flatcakes
* Name: Marlon Bustamante (917271698)
* Name: 
* Name:
* Name:
* Project: Line Following Robot
*
* File: motorShield.c
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

#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <softPwm.h>

#include "motorShield.h"

void motorSetup()
{
    // sets up wiringpi library using Broadcom pinout
    if(wiringPiSetupGpio() == -1)
    {
        printf("Failed to setup Wiring Pi!\n");
        exit(-1);
    }
    
    // setup pins as output
    printf("Setting up motor pins\n");
    
    // Motor 1
    pinMode(MOTOR_1_ENABLE, OUTPUT);
    pinMode(MOTOR_1_CONTROL, OUTPUT);
    pinMode(MOTOR_1_CONTROL_2, OUTPUT);
    
    // Motor 2
    pinMode(MOTOR_2_ENABLE, OUTPUT);
    pinMode(MOTOR_2_CONTROL, OUTPUT);
    pinMode(MOTOR_2_CONTROL_2, OUTPUT);
    
    // Motor 3
    pinMode(MOTOR_3_ENABLE, OUTPUT);
    pinMode(MOTOR_3_CONTROL, OUTPUT);
    pinMode(MOTOR_3_CONTROL_2, OUTPUT);
    
    // Motor 4
    pinMode(MOTOR_4_ENABLE, OUTPUT);
    pinMode(MOTOR_4_CONTROL, OUTPUT);
    pinMode(MOTOR_4_CONTROL_2, OUTPUT);
    
    // Setup software PWM
    softPwmCreate(MOTOR_1_ENABLE, 0, 100);  // sets the range of the PWM from 0 to 100
    softPwmCreate(MOTOR_2_ENABLE, 0, 100);
    softPwmCreate(MOTOR_3_ENABLE, 0, 100);
    softPwmCreate(MOTOR_4_ENABLE, 0, 100);
    
}

void stopMotor()
{
    printf("Stopping motors\n");
    
    // Stop motor 1
    digitalWrite(MOTOR_1_ENABLE, LOW);
    digitalWrite(MOTOR_1_CONTROL, LOW);
    digitalWrite(MOTOR_1_CONTROL_2, LOW);
    
    // Stop motor 2
    digitalWrite(MOTOR_2_ENABLE, LOW);
    digitalWrite(MOTOR_2_CONTROL, LOW);
    digitalWrite(MOTOR_2_CONTROL_2, LOW);
    
    // Stop motor 3
    digitalWrite(MOTOR_3_ENABLE, LOW);
    digitalWrite(MOTOR_3_CONTROL, LOW);
    digitalWrite(MOTOR_3_CONTROL_2, LOW);
    
    // Stop motor 4
    digitalWrite(MOTOR_4_ENABLE, LOW);
    digitalWrite(MOTOR_4_CONTROL, LOW);
    digitalWrite(MOTOR_4_CONTROL_2, LOW);
}

void moveCar(int direction)
{
    // Directions:
    // 0 == forward
    // 1 == backwords
    // 2 == left
    // 3 == right
    
    if(direction == 0)
    {
        printf("Moving car forward\n");
        
        // Setup Motor Direction
        digitalWrite(MOTOR_1_ENABLE, HIGH); // HIGH = clockwise
        digitalWrite(MOTOR_2_ENABLE, HIGH);
        digitalWrite(MOTOR_3_ENABLE, HIGH);
        digitalWrite(MOTOR_4_ENABLE, HIGH);
        
        // Move forward
        softPwmWrite(MOTOR_1_CONTROL, 100);
        softPwmWrite(MOTOR_2_CONTROL, 100);
        softPwmWrite(MOTOR_3_CONTROL, 100);
        softPwmWrite(MOTOR_4_CONTROL, 100);
    }
}