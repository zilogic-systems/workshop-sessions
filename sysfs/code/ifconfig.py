from os import listdir
from os.path import join

SYS_PATH = "/sys/class/net"

BASIC_INFO = ["address",
              "mtu",
              "statistics/rx_packets",
              "statistics/rx_errors",
              "statistics/tx_packets",
              "statistics/tx_errors",
              "statistics/rx_bytes",
              "statistics/tx_bytes"]

def cat(atdir, filename):
    path = join(atdir, filename)
    with open(path, 'r') as fp:
        data = fp.read()
    return data.strip()

def main():
    for interface in listdir(SYS_PATH):
        interface_path = join(SYS_PATH, interface)

        params = {"interface": interface}
        for info in BASIC_INFO:
            params[info] = cat(interface_path, info)

        fmt = """
{interface}\tHWaddr {address}
\tMTU:{mtu}
\tRX packets:{statistics/rx_packets} errors:{statistics/rx_errors}
\tTX packets:{statistics/tx_packets} errors:{statistics/tx_errors}
\tRX bytes:{statistics/tx_bytes} TX bytes:{statistics/tx_bytes}
""".strip()

        print(fmt.format_map(params))
        print()

if __name__ == "__main__":
    main()
