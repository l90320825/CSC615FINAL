/**************************************************************
* Class: CSC-615-01 Spring 2020
* Name: Raymond Au
* Student ID: 916672216
* Github ID: Judasilfarion
* Project: Assignment 2 - Tapeless Ruler
*
* File: assignment2.c
*
* Description: Assignment 2 wiringPi code
*
**************************************************************/

#include <stdio.h>
#include <wiringPi.h>
#include <time.h>

#define TRIG 21
#define ECHO 22

int main() {

printf("Starting tapeless ruler\n");
fflush(stdout);

if (wiringPiSetup () == -1) {
	printf("Setup failed\n");
	fflush(stdout);
	return 1;
}

printf("ECHO digi: %d\n", digitalRead(ECHO));
fflush(stdout);
printf("ECHO pin: %d\n", ECHO);
fflush(stdout);

printf("Distance measurement in progress\n");
fflush(stdout);

pinMode (TRIG, OUTPUT) ;
pinMode (ECHO, INPUT) ;

digitalWrite (TRIG,0);
printf("Waiting for sensor to settle...\n");
fflush(stdout);
delay (2000);
printf("Listening to sensor\n");
fflush(stdout);

while (1) {
struct timespec pulse_start;
struct timespec pulse_end;

digitalWrite (TRIG,1);
delayMicroseconds (10);
digitalWrite (TRIG,0);

//printf("ECHO: %d\n", digitalRead(ECHO));
//fflush(stdout);

while (digitalRead(ECHO) == 0) {
	clock_gettime(CLOCK_REALTIME, &pulse_start);
//	printf("pulse_start: %d\n", pulse_start);
//	fflush(stdout);
}

//printf("ECHO: %d\n", digitalRead(ECHO));
//fflush(stdout);

while (digitalRead(ECHO) == 1) {
	clock_gettime(CLOCK_REALTIME, &pulse_end);
//	printf("pulse_end: %d\n", pulse_end);
//	fflush(stdout);
}

//double pulse_start_sec = ((pulse_start.tv_sec * 1e9) + (pulse_start.tv_nsec)) * 1e-9;

double pulse_start_sec = ((pulse_start.tv_sec) + (pulse_start.tv_nsec * 1e-9));
double pulse_end_sec = ((pulse_end.tv_sec) + (pulse_end.tv_nsec * 1e-9));

/*
printf("pulse_start: %lf\n", pulse_start_sec);
fflush(stdout);
printf("pulse_end: %lf\n", pulse_end_sec);
fflush(stdout);
printf("distance: %f\n", (pulse_end_sec - pulse_start_sec));
fflush(stdout);
*/

double distance = (pulse_end_sec - pulse_start_sec) * 17150;

printf("Distance: %.2f cm\n", distance);
fflush(stdout);

delay(1000);
}

return 0;
}
