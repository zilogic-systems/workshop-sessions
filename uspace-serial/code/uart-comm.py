import serial

ser = serial.Serial(<serial port>, <baudrate>)
ser.write(<msg>)
ser.close()
