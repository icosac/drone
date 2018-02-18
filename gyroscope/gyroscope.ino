//// MPU-6050 Short Example Sketch
//// By Arduino User JohnChi
//// August 17, 2014
//// Public Domain
//#include<Wire.h>
//const int MPU_addr=0x68;  // I2C address of the MPU-6050
//int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;
//void setup(){
//  Wire.begin();
//  Wire.beginTransmission(MPU_addr);
//  Wire.write(0x6B);  // PWR_MGMT_1 register
//  Wire.write(0);     // set to zero (wakes up the MPU-6050)
//  Wire.endTransmission(true);
//  Serial.begin(9600);
//}
//void loop(){
//  Wire.beginTransmission(MPU_addr);
//  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
//  Wire.endTransmission(false);
//  Wire.requestFrom(MPU_addr,14,true);  // request a total of 14 registers
//  AcX=Wire.read()<<8|Wire.read();  // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)     
//  AcY=Wire.read()<<8|Wire.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
//  AcZ=Wire.read()<<8|Wire.read();  // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
//  Tmp=Wire.read()<<8|Wire.read();  // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
//  GyX=Wire.read()<<8|Wire.read();  // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
//  GyY=Wire.read()<<8|Wire.read();  // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
//  GyZ=Wire.read()<<8|Wire.read();  // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
//  Serial.print("AcX = "); Serial.print(AcX);
//  Serial.print(" | AcY = "); Serial.print(AcY);
//  Serial.print(" | AcZ = "); Serial.print(AcZ);
//  Serial.print(" | Tmp = "); Serial.print(Tmp/340.00+36.53);  //equation for temperature in degrees C from datasheet
//  Serial.print(" | GyX = "); Serial.print(GyX);
//  Serial.print(" | GyY = "); Serial.print(GyY);
//  Serial.print(" | GyZ = "); Serial.println(GyZ);
//  delay(3330);
//}









// Roll and Pitch with MPU6050
// http://www.giuseppecaccavale.it
// Giuseppe Caccavale

//#include <SPI.h>
//#include <Wire.h>
//#define MPU 0x68  // I2C address of the MPU-6050
//
//double AcX,AcY,AcZ;
//int Pitch, Roll;
//
//void setup(){
//  Serial.begin(9600);
//  init_MPU(); // Inizializzazione MPU6050
//}
// 
//void loop()
//{
//  FunctionsMPU(); // Acquisisco assi AcX, AcY, AcZ.
//    
//  Roll = FunctionsPitchRoll(AcX, AcY, AcZ);   //Calcolo angolo Roll
//  Pitch = FunctionsPitchRoll(AcY, AcX, AcZ);  //Calcolo angolo Pitch
//
//  Serial.print("Pitch: "); Serial.print(Pitch);
//  Serial.print("\t");
//  Serial.print("Roll: "); Serial.print(Roll);
//  Serial.print("\n");
//
//}
//
//void init_MPU(){
//  Wire.begin();
//  Wire.beginTransmission(MPU);
//  Wire.write(0x6B);  // PWR_MGMT_1 register
//  Wire.write(0);     // set to zero (wakes up the MPU-6050)
//  Wire.endTransmission(true);
//  delay(1000);
//}
//
////Funzione per il calcolo degli angoli Pitch e Roll
//double FunctionsPitchRoll(double A, double B, double C){
//  double DatoA, DatoB, Value;
//  DatoA = A;
//  DatoB = (B*B) + (C*C);
//  DatoB = sqrt(DatoB);
//  
//  Value = atan2(DatoA, DatoB);
//  Value = Value * 180/3.14;
//  
//  return (int)Value;
//}
//
////Funzione per l'acquisizione degli assi X,Y,Z del MPU6050
//void FunctionsMPU(){
//  Wire.beginTransmission(MPU);
//  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
//  Wire.endTransmission(false);
//  Wire.requestFrom(MPU,6,true);  // request a total of 14 registers
//  AcX=Wire.read()<<8|Wire.read();  // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)     
//  AcY=Wire.read()<<8|Wire.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
//  AcZ=Wire.read()<<8|Wire.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
//}





// Roll, Pitch and Yaw with MPU6050
// http://www.giuseppecaccavale.it
// Giuseppe Caccavale

#include <Wire.h>
#include <MPU6050.h>

MPU6050 mpu;

// Pitch, Roll and Yaw values
int pitch = 0;
int roll = 0;
float yaw = 0;

void setup() {
	Serial.begin(115200);

	Serial.println("Initialize MPU6050");

	while(!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G)){
		Serial.println("Could not find a valid MPU6050 sensor, check wiring!");
		delay(500);
	}

	// Calibrate gyroscope. The calibration must be at rest.
	// If you don't want calibrate, comment this line.
	mpu.calibrateGyro();

	// Set threshold sensivty. Default 3.
	// If you don't want use threshold, comment this line or set 0.
	mpu.setThreshold(1);

	// Check settings
	checkSettings();

	Serial.println("Everything's fine");
}

void loop(){
	// Read normalized values 
	Vector normAccel = mpu.readNormalizeAccel();
	Vector normGyro = mpu.readNormalizeGyro();

	// Calculate Pitch & Roll
	pitch = -(atan2(normAccel.XAxis, sqrt(normAccel.YAxis*normAccel.YAxis + normAccel.ZAxis*normAccel.ZAxis))*180.0)/M_PI;
	roll = (atan2(normAccel.YAxis, normAccel.ZAxis)*180.0)/M_PI;

	//Ignore the gyro if our angular velocity does not meet our threshold
	if (normGyro.ZAxis > 1 || normGyro.ZAxis < -1) {
		normGyro.ZAxis /= 100;
		yaw += normGyro.ZAxis;
	}

	//Keep our angle between 0-359 degrees
	if (yaw < 0)
		yaw += 360;
	else if (yaw > 359)
		yaw -= 360;

	// Output
	Serial.print("Pitch = ");
	Serial.print(pitch);
	Serial.print("\tRoll = ");
	Serial.print(roll);
	Serial.print("\tYaw = ");
	Serial.print(yaw);

	Serial.println();

	delay(10);
}

void checkSettings(){
	Serial.println();

	Serial.print(" * Sleep Mode:        ");
	Serial.println(mpu.getSleepEnabled() ? "Enabled" : "Disabled");

	Serial.print(" * Clock Source:      ");
	switch(mpu.getClockSource()){
		case MPU6050_CLOCK_KEEP_RESET:     Serial.println("Stops the clock and keeps the timing generator in reset"); break;
		case MPU6050_CLOCK_EXTERNAL_19MHZ: Serial.println("PLL with external 19.2MHz reference"); break;
		case MPU6050_CLOCK_EXTERNAL_32KHZ: Serial.println("PLL with external 32.768kHz reference"); break;
		case MPU6050_CLOCK_PLL_ZGYRO:      Serial.println("PLL with Z axis gyroscope reference"); break;
		case MPU6050_CLOCK_PLL_YGYRO:      Serial.println("PLL with Y axis gyroscope reference"); break;
		case MPU6050_CLOCK_PLL_XGYRO:      Serial.println("PLL with X axis gyroscope reference"); break;
		case MPU6050_CLOCK_INTERNAL_8MHZ:  Serial.println("Internal 8MHz oscillator"); break;
	}

	Serial.print(" * Gyroscope:         ");
	switch(mpu.getScale()){
		case MPU6050_SCALE_2000DPS:        Serial.println("2000 dps"); break;
		case MPU6050_SCALE_1000DPS:        Serial.println("1000 dps"); break;
		case MPU6050_SCALE_500DPS:         Serial.println("500 dps"); break;
		case MPU6050_SCALE_250DPS:         Serial.println("250 dps"); break;
	} 

	Serial.print(" * Gyroscope offsets: ");
	Serial.print(mpu.getGyroOffsetX());
	Serial.print(" / ");
	Serial.print(mpu.getGyroOffsetY());
	Serial.print(" / ");
	Serial.println(mpu.getGyroOffsetZ());

	Serial.println();
}



