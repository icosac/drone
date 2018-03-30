import RPi.GPIO as GPIO
from smbus2 import SMBus, i2c_msg
import time

# for RPI version 0, use “bus = smbus.SMBus(0)”
bus = SMBus(1)

# This is the address we setup in the Arduino Program
address = 0x04

# Send integer value to arduino
def send(value):
	msg=None
	msg=i2c_msg.write(address, [value])
	bus.i2c_rdwr(msg)
	return -1

# Receive integer value from arduino
def receive():
	msg = i2c_msg.read(address, 2)
	bus.i2c_rdwr(msg)
	number=0
	for value in msg:
		number+=value
	return value

# Send a signal to Arudino to recive a value
# 1'll be the integer to tell arduino to send back a value
def GetDistanceFromArd():
	while True:
		send(1) #1 is signal to request informations
		print("Hey Arduino, I'm asking you for a distance value")
		distance=receive()
		if (distance==504): # If the value I get is less then 0 then there was an error
			print("What's up Arudino, are you fine?")
		else: 
			print(str(count)+"Thanks, I received: "+str(number))
		count+=1;
		time.sleep(2)

if __name__=="__main__":
	GetDistanceFromArd()

# def GetDistanceFromArd():
# 	count=1
# 	while True:
# 		send(count)
# 		print(str(count)+"Hey Arduino, I'm asking you for a distance value")
# 		number=receive()
# 		if (number[0]<0): # If the value I get is less then 0 then there was an error
# 			print("What's up Arudino, are you fine?")
# 		else: 
# 			print(str(count)+"Thanks, I received: "+str(number))
# 		count+=1;
# 		time.sleep(2)