import RPi.GPIO as GPIO
import i2connection as i2c
import time

# This is the addresses where I can find Arduino
addresses = [0x04]

# Send a signal to Arudino to recive a value
def GetDistanceFromArd():
	while True:
		i2c.send1Byte(1, addresses) #1 is signal to request informations
		print("Hey Arduino, I'm asking you for a distance value")
		dist=i2c.receive2Byte(addresses)
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