/**************************************************************
* Class: CSC-615-01 Spring 2020
* Name: Raymond Au
* Student ID: 916672216
* Github ID: Judasilfarion
* Project: Assignment 5 Follow In Line But Stop
*
* File: assignment5.c
*
* Description: Assignment 5 code for IR obstacle sensor and line detector
*
**************************************************************/

#include <stdio.h>
#include <wiringPi.h>
#include <pthread.h>
#include <time.h>

#define IR 24
#define LINE 0

int exitbool = 0;
int lineDetect = 0;
int IRDetect = 0;

void *lineThread(void *vargp) {
	while (exitbool == 0) {
		lineDetect = digitalRead(LINE);
	}
	return NULL;
}

void *IRThread(void *vargp) {
	while (exitbool == 0) {
		IRDetect = digitalRead(IR);
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

pthread_t linethread_id, irthread_id, inputthread_id;
pinMode (IR, INPUT);
pinMode (LINE, INPUT);

printf("Creating threads for sensors \n");
fflush(stdout);

pthread_create(&linethread_id, NULL, lineThread, NULL);
pthread_create(&irthread_id, NULL, IRThread, NULL);

time_t seconds = time(NULL);
while (time(NULL) < seconds + 30) {
	printf("Line Sensor: %d\n", lineDetect);
	fflush(stdout);
	printf("IR Sensor: %d\n", IRDetect);
	fflush(stdout);
	delay(1000);
}

exitbool = 1;

return 0;
}
