#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <pthread.h>
#include <math.h>
#include <time.h>
#include <signal.h>
#include "arduino.h"
#include <wiringPi.h>

#ifndef	TRUE
#  define TRUE  (1==1)
#  define FALSE (1==2)
#endif

//VIRTUAL REGISTER ARDUINO
#define BUSTIME 0xAA
#define RER 0XAB // For the next feature

// Globals
FILE * busWait ;
int fd;
int min;

/*void arduino_send(int fd_arduino, int value)
{
arduino_send_byte(fd_arduino, value);
}
*/
void arduino_send(int fd_arduino, int virtualregister, int value)
{
arduino_send_word(fd_arduino, virtualregister, value);
}

static void *SendArduino (void *data)
{
 for (;;){
 busWait = fopen("187.txt", "r"); 
  if(( busWait != NULL )) { //&& (sizeof(busWait) < 2)){
  fscanf(busWait,"%d", &min) ;
  fclose (busWait) ;
  arduino_send(fd, BUSTIME, min );
  sleep (10);
  }
 }
return 0;
}

/*
 *********************************************************************************
 * main:
 *********************************************************************************
 */

int main (int argc, char *argv[])
{
//Create the thread
pthread_t bus;
fd = arduino_i2c_Begin();

//for testing only
//Usage: ./WaitingTime REGISTER VALUE 
 if (argc > 1){
 int c = atoi(argv[1]);
 int d = atoi(argv[2]);
 arduino_send(fd,c,d);
 exit (1);
 }

(void)pthread_create (&bus, NULL, SendArduino, NULL) ;
(void)pthread_join (bus, NULL);
return 0 ;
}
