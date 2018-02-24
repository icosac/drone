#include<stdio.h>
#include<wiringPi.h>
#include<math.h>

//Defined using WiringPi numeration https://pinout.xyz/#
#define READ 4 //aka BCM_18
#define ACTIVATE 5 //aka BCM_24

#define BIT 16

int bin[BIT];

double convertToDec(){
	double distance=0;
	int i=0;
	for (i; i<BIT; i++){
		distance+=bin[i]*pow(2.0, i);
	}
	return distance/100;
}

long count=0;

int main (){
	if (wiringPiSetup() == -1){
		printf("Errore nell'avvio di wiringPi\n");
		return 1;
	}

	pinMode(READ, INPUT);
	pinMode(ACTIVATE, INPUT);

	for (;;){
		if (digitalRead(ACTIVATE)==HIGH){
			printf("%i   ", count);
			delay(100);
			int i=0;
			for (i; i<BIT; i++){
				bin[i]=digitalRead(READ)==HIGH ? 1 : 0;
				delay(100);
			}
			for (i=0; i<BIT; i++){
				printf("%i", bin[i]);
			}
			printf("    %f\n", convertToDec());
			printf("\n");
			count++;
		}
	}

	return 0;
}