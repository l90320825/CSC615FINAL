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
#define LINEM 25
#define LINER 24
#define LINEL 7
#define OBSTACLE 23

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
int LDM = 0;
int LDR = 0;
int LDL = 0;

int obstacleDetect = 0;

// The target pwm of the motors
int pwm;

// Current pwm of motors L and R
int vpwmL = 0;
int vpwmR = 0;

// This thread runs a while loop that continually reads input from the line sensor in order to determine whether or not sensors detect a line.
// It currently assumes that the car only has a single line sensor - The sensor attached directly to the front of the car. Support for the other line sensors will be implemented later.
void *lineThread(void *vargp) {
	while (exitbool == 0) {

		// Read input from line sensors
		if (digitalRead(LINEM) == 1) {
			LDM = 1;
		}
		else LDM = 0;

		if (digitalRead(LINER) == 1) {
			LDR = 1;
		}
		else LDR = 0;

		if (digitalRead(LINEL) == 1) {
			LDL = 1;
		}
		else LDL = 0;



		/*
		Set the pwm of wheels based on the line sensors
		*/

		// If line sensors detect only LDM, wheels turn forward
		if (LDM == 1 && LDR == 0 && LDL == 0) {
			pwm = 50; // pwm = 50 sets the target pwm of the motors to half speed. 100 is currently way too fast for testing purposes.
		}

		// Continue moving if sensors detect nothing for a short duration so side sensors can detect line
		if (LDM == 0 && LDR == 0 && LDL == 0) {
			time_t seconds;
			seconds = time(NULL);
				while (time(NULL) < seconds + 3) {
					pwm = 50;
					if (digitalRead(LINER) == 1 || digitalRead(LINEL) == 1)
						break;
				}
			if (digitalRead(LINER) == 0 || digitalRead(LINEL) == 0)
				pwm = 0;
		}
	}
	return NULL;
}

void *obstacleThread(void *vargp) {
	while (exitbool == 0) {
		obstacleDetect = digitalRead(OBSTACLE); // Read the input from the line sensor
		if (obstacleDetect == 1) {
			int pwm = 0; // pwm = 50 sets the target pwm of the motors to half speed. 100 is currently way too fast for testing purposes.
			pwm = pwm;
		}

	}
	return NULL;
}

void changeDirection(){//Change car direction at same position
	printf("Changing Direction\n");
	for(;;){
	delay(1000);
	softPwmWrite (REVERSE1, 50);
	softPwmWrite (REVERSE2, 50);
	softPwmWrite (REVERSE3, 50);
	softPwmWrite (REVERSE4, 50);
	delay(1000);
	softPwmWrite (REVERSE1, 0);
	softPwmWrite (REVERSE2, 0);
	softPwmWrite (REVERSE3, 0);
	softPwmWrite (REVERSE4, 0);
	delay(1000);
	softPwmWrite (FORWARD1, 0);
	softPwmWrite (FORWARD2, 50);
	softPwmWrite (FORWARD3, 50);
	softPwmWrite (FORWARD4, 0);
	delay(1000);
	}
}

// This thread runs the while loop that modifies the pwm of the motors so that they can start and stop.
void *wheelThread(void *vargp) {
	while (exitbool == 0) {

		// Go forward
		if (pwm == 50 && LDM == 1) {
			// If current pwm is less than target pwm, run a loop that sets power output to motors to max (max is currently defined by pwm = 50 in the lineThread), which sets motor speed to max.
			for (vpwmL; vpwmL < pwm; vpwmL++) {
				softPwmWrite (REVERSE2, 0);
				softPwmWrite (REVERSE3, 0);
				softPwmWrite (FORWARD2, vpwmL);
				softPwmWrite (FORWARD3, vpwmL);
			}
			for (vpwmR; vpwmR < pwm; vpwmR++) {
				softPwmWrite (REVERSE1, 0);
				softPwmWrite (REVERSE4, 0);
				softPwmWrite (FORWARD1, vpwmR);
				softPwmWrite (FORWARD4, vpwmR);
			}
		}

		// Turn Right
		else if (pwm == 50 && LDR == 1 && LDL == 0) {
			// Forward left wheels
			for (vpwmL; vpwmL < pwm; vpwmL++) {
				softPwmWrite (REVERSE2, 0);
				softPwmWrite (REVERSE3, 0);
				softPwmWrite (FORWARD2, vpwmL);
				softPwmWrite (FORWARD3, vpwmL);
			}
			// Reverse right wheels
			for (vpwmR; vpwmR < pwm; vpwmR++) {
				softPwmWrite (FORWARD1, 0);
				softPwmWrite (FORWARD4, 0);
				softPwmWrite (REVERSE1, vpwmR);
				softPwmWrite (REVERSE4, vpwmR);
			}
		}

		
		// Turn Left
		else if (pwm == 50 && LDL == 1) {
			// Reverse left wheels
			for (vpwmL; vpwmL < pwm; vpwmL++) {
				softPwmWrite (FORWARD2, 0);
				softPwmWrite (FORWARD3, 0);
				softPwmWrite (REVERSE2, vpwmL);
				softPwmWrite (REVERSE3, vpwmL);
			}
			// Forward right wheels
			for (vpwmR; vpwmR < pwm; vpwmR++) {
				softPwmWrite (REVERSE1, 0);
				softPwmWrite (REVERSE4, 0);
				softPwmWrite (FORWARD1, vpwmR);
				softPwmWrite (FORWARD4, vpwmR);
			}
		}

		// Stop
		else if (pwm == 0) {
			// If current pwm is greater than target pwm, run a loop that sets power output to all motors to 0, which stops all wheels.
			for (vpwmL; vpwmL > pwm; vpwmL--) {
				softPwmWrite (FORWARD2, vpwmL);
				softPwmWrite (FORWARD3, vpwmL);
				softPwmWrite (REVERSE2, vpwmL);
				softPwmWrite (REVERSE3, vpwmL);
			}
			for (vpwmR; vpwmR > pwm; vpwmR--) {
				softPwmWrite (FORWARD1, vpwmR);
				softPwmWrite (FORWARD4, vpwmR);
				softPwmWrite (REVERSE1, vpwmR);
				softPwmWrite (REVERSE4, vpwmR);
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

// Create threads for line sensors, obstacle sensors and motors
pthread_t linethread_id, wheelthread_id, rightWheelthread_id, obstaclethread_id;
pinMode (LINEM, INPUT);
pinMode (LINER, INPUT);
pinMode (LINEL, INPUT);
pinMode (OBSTACLE, INPUT);

printf("Creating threads for sensors \n");
fflush(stdout);

pthread_create(&linethread_id, NULL, lineThread, NULL);
pthread_create(&wheelthread_id, NULL, wheelThread, NULL);
//pthread_create(&obstaclethread_id, NULL, obstacleThread, NULL);

// Runs the program for 5 minutes before shutting down
time_t seconds = time(NULL);
while (time(NULL) < seconds + 300) {
	printf("Line Sensor M: %d\n", LDM);
	printf("Line Sensor R: %d\n", LDR);
	printf("Line Sensor L: %d\n", LDL);
	fflush(stdout);
	printf("PWM: %d\n", pwm);
	fflush(stdout);
	delay(1000);
}

exitbool = 1;

return 0;
}
