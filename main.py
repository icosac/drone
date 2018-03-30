import RPi.GPIO as GPIO
from smbus2 import SMBus, i2c_msg
import time

# for RPI version 0, use “bus = smbus.SMBus(0)”
bus = SMBus(1)

# This is the addresses where I can find Arduino
addresses = [0x04]

# Send value to arduino
def send(value):
	msg=None
	for address in addresses:
		print("ok")
		msg=i2c_msg.write(address, [value])
		bus.i2c_rdwr(msg)
	return -1

# Receive value from arduino
def receive():
	number=[]
	for address in addresses:
		msg = i2c_msg.read(address, 2)
		bus.i2c_rdwr(msg)
		val=0
		for value in msg:
			val+=value
		number.append(val)
	return number

# Send a signal to Arudino to recive a value
def GetDistanceFromArd():
	while True:
		send(1) #1 is signal to request informations
		print("Hey Arduino, I'm asking you for a distance value")
		dist=receive()
		for distance in dist:
			if (distance==504): #Have a look to i4c_d.ino for codes
				print("What's up Arudino, are you fine?")
			elif (distance==503):
				print("Daaaaamn that's tooooo close")
			elif (distance==502):
				print("Man that's way too distant")
			else: 
				print("Thanks, I received: "+str(distance))
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