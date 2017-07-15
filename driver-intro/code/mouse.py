fp = open("/dev/input/mice", "rb");

while True:
    buf = fp.read(3)
    if buf[0] & 0x01:
        print("Left Button Pressed")
    if buf[0] & 0x02:
        print("Right Button Pressed")
    if buf[0] & 0x04:
        print("Middle Button Pressed")

fp.close()
