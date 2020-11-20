/**************************************************************
* Class: CSC-615-01 Spring 2020
* Name: Raymond Au
* Student ID: 916672216
* Github ID: Judasilfarion
* Project: Assignment 4 - Speed Encoder
*
* File: assignment4.c
*
* Description: Assignment 4 Speed Encoder code
*
**************************************************************/

#include <stdio.h>
#include <wiringPi.h>
#include <softPwm.h>
#include <pthread.h>
#include <time.h>

#define TRIG1 0
#define FORWARD1 2
#define REVERSE1 3
#define SENSOR 21

int exitbool = 0;
int pwm;

void *sensorThread(void *vargp) {
	time_t seconds;
	seconds = time (NULL);
	int digread = 1;
	int numpulses = 0;
	int angspeed;

	while (exitbool == 0) {
		if (digread != digitalRead(SENSOR)){
		digread = digitalRead(SENSOR);
			if (digread == 1)
				numpulses++;
		}

		delay (1);
		if (time(NULL) >= seconds + 1) {
			angspeed = (6.283185 * numpulses) / 20;
			//printf("Numpulses: %d\n", numpulses);
			float vel = (angspeed * 2.5) / 100;
			printf("PWM: %d\nSpeed: %.3f m/s\n", pwm, vel);
			fflush(stdout);
			numpulses = 0;
			seconds = time(NULL);
		}
		fflush(stdout);
	}

	printf("Closing sensorThread\n");
	fflush(stdout);
	return NULL;
}

int main(void) {

if (wiringPiSetup () == -1){
	printf("Setup failed\n");
	fflush(stdout);
	return 1;
}

printf("Setup successful\n");
fflush(stdout);

pthread_t thread_id;
pinMode (SENSOR, INPUT);

printf("Creating sensorThread\n");
fflush(stdout);

pthread_create(&thread_id, NULL, sensorThread, NULL);

printf("sensorThread creation successful\n");
fflush(stdout);

pinMode (TRIG1, 1);
pinMode (FORWARD1, 1);
pinMode (REVERSE1, 1);
digitalWrite (TRIG1, 1);

softPwmCreate (FORWARD1, 1, 100);

printf("Activating motor\n");
fflush(stdout);

for (pwm = 20; pwm < 101; pwm++) {
	softPwmWrite (FORWARD1, pwm);
	delay (20);
}
delay(5000);

for (pwm = 100; pwm >= 0; pwm--) {
	softPwmWrite (FORWARD1, pwm);
	delay(20);
}

delay(1500);

digitalWrite (TRIG1, 0);

printf("Program end\n");
fflush(stdout);

exitbool = 1;

return 0;

}
