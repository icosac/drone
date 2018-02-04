#include<stdio.h>
#include<wiringPi.h>
#include <sys/time.h>

#define echo 3 //aka BCM_22 pin 15
#define trig 4 //aka BCM_23 pin 16

int main (){
	struct timeval stop, start;
	// printf("took %lu\n", stop.tv_usec - start.tv_usec);

	if (wiringPiSetup () == -1){
        printf("Errore nell'avvio di wiringPi");
        return 1 ;
    }
    pinMode (echo, INPUT); //Set echo to INPUT
    pinMode (trig, OUTPUT); //Set trig to OUTPUT
    for (;;){
        //set Trigger to HIGH
	    digitalWrite(trig, HIGH);

	    //set Trigger after 0.01ms to LOW
	    delay(0.00001);
	    digitalWrite(trig, LOW);
        
        while(digitalRead(echo)==LOW){
			gettimeofday(&start, NULL);
        }

        while(digitalRead(echo)==HIGH){
			gettimeofday(&stop, NULL);
        }
		
        unsigned long long elapsed=stop.tv_usec-start.tv_usec;

        printf("Trascorso %u\n", elapsed);
        printf("Distanza: %f\n", (elapsed*0.0343));
        delay(500);
    }
	return 0;
}