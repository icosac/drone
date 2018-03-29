#include<stdio.h>
#include<wiringPiI2C.h>

#define ADDR 0x08

int fd;

int main (){
	fd=wiringPiI2CSetup(ADDR);
	int i; 
	for (i=0; i<10; i++){
		printf("Mando: %d", i);
		wiringPiI2CWriteReg8(fd, 0, i);
		delay(100);
	}
	return 0;
}