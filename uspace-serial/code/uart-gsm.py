import serial
from time import sleep

mode_cmd = b'AT+CMGF=1\r\n'
msg_cmd = b'AT+CMGS=<phone_number>\r\n'
msg = b'Hello\x1A'

def sendmsg(msg):
    phone.write(msg)
    phone.flush()
    sleep(1)

phone = open('/dev/ttyUSB0', 'wb')

sendmsg(mode_cmd)
sendmsg(msg_cmd)
sendmsg(msg)

phone.close()
