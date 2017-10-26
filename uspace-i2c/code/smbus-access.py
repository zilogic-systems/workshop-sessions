import smbus

BUSNO = 0
SLAVE = <slave address>
REG = <reg addr>

i2c = smbus.SMBus(BUSNO)
i2c.open(BUSNO)

data = i2c.read_byte_data(SLAVE, REG)
