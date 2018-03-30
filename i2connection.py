#TODO convert in binary and send / receive in binary and convert. Not really needed cause 5 meters is already too far
from smbus2 import SMBus, i2c_msg

bus=SMBus(1) #Initialize protocol

######## ####### #	   # ###### 
#        #       ##    # #     #
#        #       # #   # #     #
######## #####   #  #  # #     #
       # #       #   # # #     #
       # #       #    ## #     #
######## ####### #     # ######

#Returns 1 if the message was sent correctly, -1 if not.

# Send value to arduinos in addresses list
# value: list of bytes to be sent
# address: list of i2c addresses to send value
def sendNByte(value, addresses):
	msg=None #Need to re-initialize
	for address in addresses:
		try:
			msg=i2c_msg.write(address, value)
		except Exception:
			return -1
		try:
			bus.i2c_rdwr(msg)
		except Exception:
			return -1
	return 1

#Send a single byte
def send1Byte(value, addresses):
	if value < 255 and value>=0:
		return sendNByte([value], addresses)
	else:
		return -1


#######  ####### ####### # #       # #######
#      # #       #       #  #     #  #
#      # #       #       #  #     #  #
#     #  ######  #       #   #   #   ######
#  #     #       #       #   #   #   #
#    #   #       #       #    # #    #
#      # ####### ####### #     #     #######

#Returns the value obtained. None if there was an error

# Receive value from arduinos in addresses list
# N number of byte to read
# adddress list of addresses to read from
def receiveNByte(N, addresses):
	number=[]
	for address in addresses:
		try:
			msg = i2c_msg.read(address, N)
		except Exception:
			return None
		try: 
			bus.i2c_rdwr(msg)
		except Exception:
			return None
		val=0
		for value in msg: 
			val+=value #Sommo i valori dei vari bit.
		number.append(val)
	return number

# Receive 2 bytes from arduinos in addresses list
# adddress list of addresses to read from
def receive2Byte(addresses):
	return receiveNByte(2, addresses)