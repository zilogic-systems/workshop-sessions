import re

from os import listdir
from os.path import join

sys_path = "/sys/class/block/"

def read_path(*args):
    path = join(sys_path, *args)
    return open(path, 'r').read()[:-1]

print("Partition\tSize(in MB)")

for file in listdir(sys_path):
    if re.match("sda[0-9]", file):
        raw_size = read_path(sys_path, file, "size")
        raw_size = int(raw_size)
        size = (raw_size * 512) / (1024 * 1024)
        size = int(size)
        if (size != 0):
            print("{}\t\t{}".format(file, size))
