import serial
import sys
port=sys.argv[1]
ser = serial.Serial(port, 9600)
while True:
	try:
		distance = float(ser.readline())
		print distance
	except (KeyboardInterrupt, SystemExit):
		break
	except:
		pass
