/************************************************************** * Class: CSC-615-01 Spring 2020 * Name: Raymond 
Au * Student ID: 916672216 * Github ID: Judasilfarion * Project: Assignment 5 Follow In Line But Stop * * File: 
assignment5.c * * Description: Assignment 5 code for IR obstacle sensor and line detector * 
**************************************************************/

#include <stdio.h>
#include <wiringPi.h>
#include <pthread.h>
#include <time.h>
#include <softPwm.h>

// GPIO pin for the line sensor
#define LINE 25

// GPIO pins for turning on the motors, probably don't need to touch these
#define TRIG1 0
#define TRIG2 6
#define TRIG3 12
#define TRIG4 26

// GPIO pins for power output to the motors, used to make them spin
#define FORWARD1 2 	// Right rear wheel
#define FORWARD2 4 	// Left rear wheel
#define FORWARD3 14 	// Left front wheel
#define FORWARD4 10 	// Right front wheel
#define REVERSE1 3 	// Right rear wheel
#define REVERSE2 5 	// Left rear wheel
#define REVERSE3 13 	// Left front wheel
#define REVERSE4 11 	// Right front wheel

// Used to determine whether or not the program should shut down all threads and exit
int exitbool = 0;

// If this is 1, then the car detects the line. If this is 0, then the car does not detect the line
int lineDetect = 0;

// The target pwm of the motors
int pwm;

// The current pwm of the motors
int vpwm = 0;

// This thread runs a while loop that continually reads input from the line sensor in order to determine whether or not sensors detect a line.
// It currently assumes that the car only has a single line sensor - The sensor attached directly to the front of the car. Support for the other line sensors will be implemented later.
void *lineThread(void *vargp) {
	while (exitbool == 0) {
		lineDetect = digitalRead(LINE); // Read the input from the line sensor
		if (lineDetect == 1) {
			pwm = 50; // pwm = 50 sets the target pwm of the motors to half speed. 100 is currently way too fast for testing purposes.
		}
		else pwm = 0;
	}
	return NULL;
}

// This thread runs the while loop that modifies the pwm of the motors so that they can start and stop.
void *wheelThread(void *vargp) {
	while (exitbool == 0) {
		if (vpwm < pwm) {
			// If current pwm is less than target pwm, run a loop that sets power output to all motors to max (max is currently defined by pwm = 50 in the lineThread), which sets motor speed to max.
			for (vpwm; vpwm < pwm; vpwm++) {
				softPwmWrite (FORWARD1, vpwm);
				softPwmWrite (FORWARD2, vpwm);
				softPwmWrite (FORWARD3, vpwm);
				softPwmWrite (FORWARD4, vpwm);
			}
		}
		if (vpwm > pwm) {
			// If current pwm is greater than target pwm, run a loop that sets power output to all motors to 0, which stops all wheels.
			for (vpwm; vpwm > pwm; vpwm--) {
				softPwmWrite (FORWARD1, vpwm);
				softPwmWrite (FORWARD2, vpwm);
				softPwmWrite (FORWARD3, vpwm);
				softPwmWrite (FORWARD4, vpwm);
			}
		}
	}
	return NULL;
}

// Main function
int main (void) {

// Setup wiringpi
if (wiringPiSetup () == -1){
	printf("Setup failed\n");
	fflush(stdout);
	return 1;
}

printf("Setup successful\n");
fflush(stdout);

// Turn on motors
pinMode (TRIG1, 1);
pinMode (TRIG2, 1);
pinMode (TRIG3, 1);
pinMode (TRIG4, 1);
digitalWrite (TRIG1, 1);
digitalWrite (TRIG2, 1);
digitalWrite (TRIG3, 1);
digitalWrite (TRIG4, 1);

// Create pwm for motors
softPwmCreate (FORWARD1, 0, 100);
softPwmCreate (FORWARD2, 0, 100);
softPwmCreate (FORWARD3, 0, 100);
softPwmCreate (FORWARD4, 0, 100);
softPwmCreate (REVERSE1, 0, 100);
softPwmCreate (REVERSE2, 0, 100);
softPwmCreate (REVERSE3, 0, 100);
softPwmCreate (REVERSE4, 0, 100);

// Create threads for line sensor and motors
pthread_t linethread_id, wheelthread_id;
pinMode (LINE, INPUT);

printf("Creating threads for sensors \n");
fflush(stdout);

pthread_create(&linethread_id, NULL, lineThread, NULL);
pthread_create(&wheelthread_id, NULL, wheelThread, NULL);

// Runs the program for 5 minutes before shutting down
time_t seconds = time(NULL);
while (time(NULL) < seconds + 300) {
	printf("Line Sensor: %d\n", lineDetect);
	fflush(stdout);
	printf("PWM: %d\n", pwm);
	fflush(stdout);
	delay(1000);
}

exitbool = 1;

return 0;
}
