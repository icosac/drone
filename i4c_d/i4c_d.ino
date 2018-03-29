#include <Wire.h>

#define SLAVE_ADDRESS 0x04 // This is the address on which I'll be talking with Pi
int distance = 0; //The distance I'm measuring. Set to -1 if there's been an error
int signal=0; //The value received from Pi

void setup() {
	Serial.begin(9600); // Start serial for output
	// initialize i2c as slave
	Wire.begin(SLAVE_ADDRESS);

	// define callbacks for i2c communication
	Wire.onReceive(receiveData);
	Wire.onRequest(sendData);

	Serial.println("I'm ready!");
	randomSeed(analogRead(0));
}

void loop() {
	delay(1000);
	distance=random(-2, 11);
	Serial.print("distance: ");Serial.println(distance);
}

// I'm listening for anything from my friend Pi
void receiveData(int byteCount){
	while(Wire.available()) {
		signal = Wire.read(); 
		Serial.print("Data received: ");
		Serial.println(signal);
	}
}

// I'll send data to my friend Pi
void sendData(){
	if (signal > 0){
		Wire.write(distance);
		Serial.print("Sent: ");Serial.print(distance);Serial.print(" for request: ");Serial.println(signal);
	}
	else {
		Serial.print("Got");Serial.print(signal);Serial.println(", I don't recognize this value");
	}
}