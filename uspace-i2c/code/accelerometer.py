import smbus
from time import sleep
import struct

BUS_NO = 0          # Accelerometer is connected to i2c bus 0.
ACC_ADDR = 0x1C     # Slave address of Accelerometer.
CTRL_REG1 = 0x2A    # Accelerometer control reg to set enable mode.
ENABLE = 0x01       # Enable bit.
SCALE = 2 / 128     # Acceleration is from +128 to -128

def twos_complement(data):
    if data & 0x80:
        return -((~data & 0xFF)+ 1)
    else:
        return data

acc = smbus.SMBus(BUS_NO)
acc.open(BUS_NO)
acc.write_byte_data(ACC_ADDR, CTRL_REG1, ENABLE)
acc.write_byte(ACC_ADDR, 0x00)

while True:
    data = acc.read_i2c_block_data(ACC_ADDR, 0x00)
    x = twos_complement(data[1]) * SCALE
    y = twos_complement(data[3]) * SCALE
    z = twos_complement(data[5]) * SCALE

    print("x={0:.2}g y={1:.2}g z={2:.2}g".format(x, y, z))

    sleep(1)
