from time import sleep

mode_cmd = b'AT+CMGF=1\r\n'
msg_cmd = b'AT+CMGS=+919952529375\r\n'
msg = b'Hello\x1A'
phone = open('/dev/ttyUSB0', 'wb')

def sendmsg(msg):
    phone.write(msg)
    phone.flush()
    sleep(2)

print("Setting Text mode...", end='')
sendmsg(mode_cmd)
print("Done.")
print("Selecting given number for messaging...", end='')
sendmsg(msg_cmd)
print("Done.")
print("Sending \"Hello\" to the number...", end='')
sendmsg(msg)
print("Done.")

phone.close()
