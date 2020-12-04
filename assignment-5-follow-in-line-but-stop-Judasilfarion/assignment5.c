/************************************************************** * Class: CSC-615-01 Spring 2020 * Name: Raymond 
Au * Student ID: 916672216 * Github ID: Judasilfarion * Project: Assignment 5 Follow In Line But Stop * * File: 
assignment5.c * * Description: Assignment 5 code for IR obstacle sensor and line detector * 
**************************************************************/

#include <stdio.h>
#include <wiringPi.h>
#include <pthread.h>
#include <time.h>
#include <softPwm.h>

#define LINE 25
#define TRIG1 0
#define TRIG2 6
#define TRIG3 12
#define TRIG4 26
#define FORWARD1 3
#define FORWARD2 5
#define FORWARD3 13
#define FORWARD4 11

int exitbool = 0;
int lineDetect = 0;
int pwm;
int vpwm = 0;

void *lineThread(void *vargp) {
	while (exitbool == 0) {
		lineDetect = digitalRead(LINE);
		if (lineDetect == 0) {
			pwm = 100;
		}
		else pwm = 0;
	}
	return NULL;
}

void *wheelThread(void *vargp) {
	while (exitbool == 0) {
		if (vpwm < pwm) {
			for (vpwm; vpwm < pwm; vpwm++) {
				softPwmWrite (FORWARD1, vpwm);
				softPwmWrite (FORWARD2, vpwm);
				softPwmWrite (FORWARD3, vpwm);
				softPwmWrite (FORWARD4, vpwm);
			}
		}
		if (vpwm > pwm) {
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

int main (void) {
if (wiringPiSetup () == -1){
	printf("Setup failed\n");
	fflush(stdout);
	return 1;
}

printf("Setup successful\n");
fflush(stdout);

pinMode (TRIG1, 1);
pinMode (TRIG2, 1);
pinMode (TRIG3, 1);
pinMode (TRIG4, 1);
digitalWrite (TRIG1, 1);
digitalWrite (TRIG2, 1);
digitalWrite (TRIG3, 1);
digitalWrite (TRIG4, 1);

softPwmCreate (FORWARD1, 0, 100);
softPwmCreate (FORWARD2, 0, 100);
softPwmCreate (FORWARD3, 0, 100);
softPwmCreate (FORWARD4, 0, 100);

pthread_t linethread_id, wheelthread_id;
pinMode (LINE, INPUT);

printf("Creating threads for sensors \n");
fflush(stdout);

pthread_create(&linethread_id, NULL, lineThread, NULL);
pthread_create(&wheelthread_id, NULL, wheelThread, NULL);

time_t seconds = time(NULL);
while (time(NULL) < seconds + 30) {
	printf("Line Sensor: %d\n", lineDetect);
	fflush(stdout);
	printf("PWM: %d\n", pwm);
	fflush(stdout);
	delay(1000);
}

exitbool = 1;

return 0;
}
