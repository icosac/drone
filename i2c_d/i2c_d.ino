#include<Wire.h>

#define ADDR 0x08

int number=0, state=0, a=0;
int arr[65536];

void setup(){
	Serial.begin(9600);
	Wire.begin(ADDR);
	Wire.onReceive(receiveData);
	Wire.onRequest(sendData);
}

void loop(){
	receiveData();
	delay(100);
	if (number==0xFF){
		Serial.println("Ci sono, arrivo");
		number=96;
		sendData();
	}
	delay(1000);
}

void receiveData (){
	while(Wire.available()) {
		number = Wire.read();
		Serial.print("number: ");
		Serial.println(number);
		// if (a!=number){
		// 	Serial.print("Diff: ");
		// 	Serial.println(number);
		// }
		// arr[a]=number;
		// a++;
		if (number == 1){
			if (state == 0){
				digitalWrite(13, HIGH); // set the LED on
				state = 1;
			}
			else{
				digitalWrite(13, LOW); // set the LED off
				state = 0;
			}
		}
	}
	// if (a==65535){
	// 	for (a=0; a<65535; a++){
	// 		Serial.println(arr[a]);
	// 	}
	// }
}

void sendData (){
	 Wire.write(number);
}




