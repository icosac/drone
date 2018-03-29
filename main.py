import RPi.GPIO as GPIO
import smbus
import time

# for RPI version 0, use “bus = smbus.SMBus(0)”
bus = smbus.SMBus(1)

# This is the address we setup in the Arduino Program
address = 0x04

# Send integer value to arduino
def send(value):
	bus.write_byte(address, value)
	# bus.write_byte_data(address, 0, value)
	return -1

# Receive integer value from arduino
def receive():
	number = bus.read_byte(address)
	# number = bus.read_byte_data(address, 1)
	return number

# Send a signal to Arudino to recive a value
# 1'll be the integer to tell arduino to send back a value
def GetDistanceFromArd():
	count=1
	while True:
		send(count)
		print(str(count)+"Hey Arduino, I'm asking you for a distance value")
		number=receive()
		if (number<0): # If the value I get is less then 0 then there was an error
			print("What's up Arudino, are you fine?")
		else: 
			print(str(count)+"Thanks, I received: "+str(number))
		count+=1;
		time.sleep(2)

if __name__=="__main__":
	GetDistanceFromArd()

	