import struct
from math import ceil

KB = 1000
MB = KB * 1000
GB = MB * 1000

def human_readable(size):
    if size > GB:
        return "{0:.1f} GB".format(ceil(size / GB))
    elif size > MB:
        return "{0:.1f} MB".format(ceil(size / MB))
    elif size > KB:
        return "{0:.1f} KB".format(ceil(size / KB))
    else:
        return "{0} bytes".format(size)

def print_parts(device):
    fp = open(device, "rb")
    fp.read(446)

    for i in range(4):
        pt_entry = fp.read(16)
        active, ptype, start, size = struct.unpack("BxxxBxxxII", pt_entry)

        if size == 0:
            continue

        start = human_readable(start * 512)
        size = human_readable(size * 512)
        print("{0} {1:10} {2:10}".format(i+1, start, size))

if __name__ == "__main__":
    print_parts("/dev/sda")
