#!/usr/bin/env python

import socket
import sys
import time

# Converts a number to a bitstream with specified bitlength
# Returns the value as a list of bitlength / 8 characters
def Bits(val, size):
	res = []
   
	i = 0
	while(i < size/8) :
		res.append(val%256)
		val  = int(val/256)
		i   += 1
		
	return res

	
	
# STATE OF THE ROBOT CAR
leftDirection  = 1	# Direction of the left motor (1 = Forward, 0 = Backward)
rightDirection = 0	# Direction of the right motor (1 = Forward, 0 = Backward)
leftSpeed  = 255	# Speed of the left motor
rightSpeed = 255	# Speed of the left motor
servoAngle = 180	# Angle of the micro servo, 90 degree is middle 
usDistance = 300	# Distance reading of the ultrasonic sensor in centimeters
infrared1  = 1		# Reading of the Infrared Sensor 1
infrared2  = 0		# Reading of the Infrared Sensor 2
infrared3  = 0		# Reading of the Infrared Sensor 3
infrared4  = 1		# Reading of the Infrared Sensor 4


print( ord(chr(255)) )

# Create a socket, bind it to localhost:5005 and listen on it
server_address = ('127.0.0.1', 5005)
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sock.bind(server_address)
sock.listen(1)

# Wait for connection
connection, client_address = sock.accept()

# create byte array for sending the state of the car (FAULTY)
data =  []
data += Bits(leftDirection, 8)
data += Bits(rightDirection,8)
data += Bits(leftSpeed, 16)
data += Bits(rightSpeed,16)
data += Bits(servoAngle,16)
data += Bits(usDistance,32)
data += Bits(infrared1,8)
data += Bits(infrared2,8)
data += Bits(infrared3,8)
data += Bits(infrared4,8)

# Keep sending the data every second
while True:
	connection.sendall(bytes(data))
	time.sleep(1)
	

