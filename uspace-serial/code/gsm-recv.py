import serial

ser = serial.Serial('/dev/ttyUSB0', 115200)

test_cmd = b'AT\r\n'
text_mode = b'AT+CMGF=1\r\n'
notify_msg = b'AT+CNMI=2,2,0,0,0\r\n'

def gsm_recv():
    ser.flushInput()
    ser.write(notify_msg)
    print("Waiting for Message...")
    while True:
        if 'CMT' in str(ser.readline()):
            recvmsg = str(ser.readline())
            print(recvmsg.strip())
        ser.write(b'\r\n')

def gsm_init():
    ser.write(test_cmd)
    ser.write(text_mode)

gsm_init()
gsm_recv()
