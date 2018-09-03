import serial

#Create bluetooth serial port
btport = serial.Serial('/dev/rfcomm0')
#Create USB Serial Port
frdmport = serial.Serial('/dev/ttyACM0')

while(1):
        try:
        		#Pass two chars from bluetooth input to USB serial output
                frdmport.write(btport.read(2))
        except:
                pass
