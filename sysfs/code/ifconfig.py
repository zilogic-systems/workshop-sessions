from os import listdir
from os.path import join

sys_path = "/sys/class/net"

basic_info = ["address", "mtu"]

statistics_info = ["rx_packets", "rx_errors",
                   "tx_packets", "tx_errors",
                   "rx_bytes", "tx_bytes"]

def read_path(*args):
    path = join(sys_path, *args)
    return open(path, 'r').read()[:-1]

for interface in listdir(sys_path):
    for info in basic_info:
        exec('%s = "%s"' % (info, read_path(interface, info)))

    print('{}\tHWaddr {}'.format(interface, address))
    print('\tMTU:{}'.format(mtu))

    for info in statistics_info:
        exec('%s = "%s"' % (info, read_path(interface, "statistics", info)))

    print('\tRX packets:{} errors:{}'.format(rx_packets, rx_errors))
    print('\tTX packets:{} errors:{}'.format(tx_packets, tx_errors))
    print('\tRX bytes:{}\tTX bytes:{}'.format(rx_bytes, tx_bytes))
    print('')
