/**************************************************************
* Class:  CSC-615-01 Spring 2020
* Team: Tuna Flatcakes
* Name: Marlon Bustamante (917271698)
* Name: 
* Name:
* Name:
* Project: Line Following Robot
*
* File: lineRobot.c
*
* Description: 
*
**************************************************************/ 

#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <softPwm.h>
#include <signal.h>

#include "motorShield.h"

void setup()
{
    motorSetup();
}

void cleanup()
{
    printf("Disabling Components\n");
    stopMotor();
    exit(0);
}

int main(void)
{
    signal(SIGINT, cleanup);
    
    printf("Starting line robot\n");
    
    setup();
    
    moveCar(0); // move car forward
    while(1){}
    
    printf("Stopping line robot\n");
    cleanup();
    
    return 0;
}