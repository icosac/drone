// Since i2c sends one byte per time, I'll send 2 bytes. This are the error codes:
// If distance is:
// >500 => 502 send byte1=0xFF=255, byte2=0xF7=247 
// <=0 => 503 send byte1=0xFF=255, byte2=0xF7=248
// If signal was not recognized: 504 send byte1=0xFF=255, byte2=0xF7=249 

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
	distance=random(-2, 3);
	if (distance==-2){
		distance=550;
	}
	else if (distance==0){
		distance==400;
	}
	Serial.print("distance: ");Serial.println(distance);
}

// I'm listening for anything from my friend Pi
void receiveData(int byteCount){
	while(Wire.available()) {
		signal = Wire.read(); 
		Serial.print("Signal received: "); Serial.println(signal);
	}
}

// I'll send data to my friend Pi
// See top of document for information regarding error codes.
void sendData(){
	byte byte1, byte2;
	if (signal > 0){ //Change with ==1
		if (distance>500){
			byte1=0xff; byte2=0xf7; //255+247=502
		}
		else if (distance<=0){
			byte1=0xff; byte2=0xf8; //255+248=503
		}
		else if (distance>255 && distance <=500){
			byte1=0xff; byte2=(byte)distance-0xff;
		}
		else {
			byte1=(byte)distance; byte2=0x00;
		}
		Serial.print("Sent: ");Serial.print(byte1);Serial.print("; ");Serial.println(byte2);
	}
	else {
		byte1=0xff; byte2=0xf9;
		Serial.print("Got");Serial.print(signal);Serial.println(", I don't recognize this value");
	}
	byte buffer[2]={byte1, byte2};
	Wire.write(buffer, 2);
	Serial.print("Sent: ");Serial.print(byte1);Serial.print("; ");Serial.println(byte2);
}