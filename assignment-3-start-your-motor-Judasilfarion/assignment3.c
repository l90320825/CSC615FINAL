/**************************************************************
* Class: CSC-615-01 Spring 2020
* Name: Raymond Au
* Student ID: 916672216
* Github ID: Judasilfarion
* Project: Assignment 3 - Start Your Engines
*
* File: pimotor.c
*
* Description: Assignment 3 Pi Motor code
*
**************************************************************/

#include <stdio.h>
#include <wiringPi.h>
#include <softPwm.h>

#define TRIG1 0
#define FORWARD1 2
#define REVERSE1 3
#define TRIG2 6
#define FORWARD2 4
#define REVERSE2 5

int main(void) {

if (wiringPiSetup () == -1){
	printf("Setup failed\n");
	fflush(stdout);
	return 1;
}

printf("Setup successful\n");
fflush(stdout);

printf("Setting up PWM\n");
fflush(stdout);
delay(1000);

int pwm;

pinMode (TRIG1, 1);
pinMode (FORWARD1, 1);
pinMode (TRIG2, 1);
pinMode (FORWARD2, 1);
digitalWrite (TRIG1, 1);
digitalWrite (TRIG2, 1);

softPwmCreate(FORWARD1, 1, 100);
softPwmCreate(FORWARD2, 1, 100);

	for (pwm = 0; pwm < 101; pwm++){
		softPwmWrite (FORWARD1, pwm);
		softPwmWrite (FORWARD2, pwm);
		delay (1);
	}
	delay(1000);
	
	for (pwm = 100; pwm >= 0; pwm--) {
		softPwmWrite (FORWARD1, pwm);
		softPwmWrite (FORWARD2, pwm);
		delay (1);
	}
	delay (1000);

softPwmCreate(REVERSE1, 1, 100);
softPwmCreate(REVERSE2, 1, 100);

        for (pwm = 0; pwm < 101; pwm++){
                softPwmWrite (REVERSE1, pwm);
                softPwmWrite (REVERSE2, pwm);
		delay (1);
        }
        delay(1000);

        for (pwm = 100; pwm >= 0; pwm--) {
                softPwmWrite (REVERSE1, pwm);
		softPwmWrite (REVERSE2, pwm);
                delay (1);
        }
	delay(1000);

printf("Half speed\n");
fflush(stdout);

        for (pwm = 0; pwm < 50; pwm++){
                softPwmWrite (FORWARD1, pwm);
		softPwmWrite (FORWARD2, pwm);
                delay (1);
        }
        delay(1000);

        for (pwm = 51; pwm >= 0; pwm--) {
                softPwmWrite (FORWARD1, pwm);
		softPwmWrite (FORWARD2, pwm);
                delay (1);
        }
        delay (1000);


        for (pwm = 0; pwm < 50; pwm++){
                softPwmWrite (REVERSE1, pwm);
                softPwmWrite (REVERSE2, pwm);
                delay (1);
        }
        delay(1000);

        for (pwm = 51; pwm >= 0; pwm--) {
                softPwmWrite (REVERSE1, pwm);
                softPwmWrite (REVERSE2, pwm);
                delay (1);
        }

digitalWrite (TRIG1, 0);
digitalWrite (TRIG2, 0);

printf("Program end\n");
fflush(stdout);

return 0;
}
