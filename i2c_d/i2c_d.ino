#include<Wire.h>

#define ADDR 0x08

int number=0, state=0;

void setup(){
	Serial.begin(9600);
	Wire.begin(ADDR);
	Wire.onReceive(receiveData);
	Wire.onRequest(sendData);
}

void loop(){
	delay(100);
}

void receiveData (){
	while(Wire.available()) {
		number = Wire.read();
		Serial.print("data received: ");
		Serial.println(number);
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
}

void sendData (){
	 Wire.write(number);
}