import smbus
from time import sleep
import struct

BUS_NO = 0
ACC_ADDR = 0x1C
CTRL_REG1 = 0x2A
STATUS = 0x00
ZYX_DR = 0x08


def is_data_ready(acc):
    status = acc.read_byte_data(ACC_ADDR, STATUS) & ZYX_DR
    return status

def twos_compliment(data):
    axis = struct.unpack('b', bytes([data]))
    return axis[0]

def read_xyz_data(acc):

    if is_data_ready(acc):
        x_msb = acc.read_byte_data(ACC_ADDR, STATUS + 1)
        x = twos_compliment(x_msb) * 4 / 256

        y_msb = acc.read_byte_data(ACC_ADDR, STATUS + 3)
        y = twos_compliment(y_msb) * 4 / 256

        z_msb = acc.read_byte_data(ACC_ADDR, STATUS + 5)
        z = twos_compliment(z_msb) * 4 / 256

        print("x={0:.2} y={1:.2}, z={2:.2}".format(x, y, z))
    else:
        print("Device busy. Try again.")


def set_active(acc, enable_flag):
    active_bit = 0
    acc.write_byte_data(ACC_ADDR, CTRL_REG1, (enable_flag << active_bit))


def acc_init(acc):
    set_active(acc, 1)


def main():
    acc = smbus.SMBus(BUS_NO)
    acc.open(BUS_NO)

    acc_init(acc)

    while True:
        read_xyz_data(acc)
        sleep(1)

main()
