#include<stdio.h>
#include<wiringPiI2C.h>

#define ADDR 0x08

int fd;

int main (){
	fd=wiringPiI2CSetup(ADDR);
	int i; 
	for (i=0x00; i<0xFF; i++){
		printf("Mando: %x", i);
		wiringPiI2CWrite(fd, i);	
	}
	return 0;
}