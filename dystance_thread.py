import RPi.GPIO as GPIO
import time

#GPIO Mode (BOARD / BCM)
GPIO.setmode(GPIO.BCM)
 
#set GPIO Pins
READ = 18
ACTIVATE = 24

#set GPIO direction (IN / OUT)
GPIO.setup(READ, GPIO.IN)
GPIO.setup(ACTIVATE, GPIO.IN)

number=[]

def main ():
	while True:
		print(GPIO.input(ACTIVATE))
		if GPIO.input(ACTIVATE)==0:
			time.sleep(0.0001)
			for i in range (0, 15):
				number.append(GPIO.input(READ))
				time.sleep(0.0001)
			print(number)


if __name__== "__main__":
	try:
		main()
	# Reset by pressing CTRL + C
	except KeyboardInterrupt:
		print("Measurement stopped by User")
		GPIO.cleanup()