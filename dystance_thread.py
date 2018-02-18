import RPi.GPIO as GPIO

#GPIO Mode (BOARD / BCM)
GPIO.setmode(GPIO.BCM)
 
#set GPIO Pins
READ = 18
ACTIVATE = 24

#set GPIO direction (IN / OUT)
GPIO.setup(READ, GPIO.IN)
GPIO.setup(ACTIVATE, GPIO.IN)

number=[]

def main (argv):
	while True:
		if GPIO.input(ACTIVATE)==1:
			for i in range (15, 0):
				number.append(GPIO.input(READ))
			print(number)


if __name__== "__main__":
	main ()