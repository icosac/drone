#Libraries
import RPi.GPIO as GPIO
import time

#GPIO Mode (BOARD / BCM)
GPIO.setmode(GPIO.BCM)

#set GPIO Pins
GPIO_TRIGGER1 = 18
GPIO_ECHO1 = 24

GPIO_TRIGGER2 = 23
GPIO_ECHO2 = 25

#set GPIO direction (IN / OUT)
GPIO.setup(GPIO_TRIGGER1, GPIO.OUT)
GPIO.setup(GPIO_ECHO1, GPIO.IN)
GPIO.setup(GPIO_TRIGGER2, GPIO.OUT)
GPIO.setup(GPIO_ECHO2, GPIO.IN)

arr1=[]
arr2=[]
frr=[]

def average(arr_):
    av=0;
    l=len(arr_)
    for i in arr_:
        av=av+i
    del arr_[:]
    return (av/l)

def distance():
    for i in range(0, 10):    
        # set Trigger to HIGH
        GPIO.output(GPIO_TRIGGER1, True)
        print("trig set")

        # set Trigger after 0.01ms to LOW
        time.sleep(0.00001)
        GPIO.output(GPIO_TRIGGER1, False)
        print("trig unset")

        StartTime = time.time()
        StopTime = time.time()
        print("time defined")

        timer=time.time()+1
        # save StartTime
        while GPIO.input(GPIO_ECHO1) == 0 and time.time()<timer:
            StartTime = time.time()
        print ("nice")

        # save time of arr1ival
        while GPIO.input(GPIO_ECHO1) == 1:
            StopTime = time.time()
        print ("wow") 
        # time difference between start and arr1ival
        TimeElapsed = StopTime - StartTime
        # multiply with the sonic speed (34300 cm/s)
        # and divide by 2, because there and back
        distance = (TimeElapsed * 34300) / 2
        arr1.append(distance)
        # print("arr1: "+str(arr1))
        time.sleep(0.0001)

    return average(arr1)

if __name__ == '__main__':
    try:
        print("OK")
        while True:
        dist = distance()
        print ("Measured Distance = %.1f cm" % dist)
        frr.append(dist)
        time.sleep(1)

    # Reset by pressing CTRL + C
    except KeyboardInterrupt:
        print("Measurement stopped by User")
        print(str(frr))
        print(str(average(frr)))
        GPIO.cleanup()