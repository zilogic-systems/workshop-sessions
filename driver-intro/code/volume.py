import struct
import fcntl
import ioctl

def split_lr(volume):
    left = volume & 0xff;
    right = (volume & 0xff00) >> 8;
    return (left, right)

def join_lr(left, right):
    return left | (right << 8);


volume_bytes = bytearray(struct.calcsize("i"))
fp = open("/dev/mixer")

fcntl.ioctl(fp, ioctl.SOUND_MIXER_READ_VOLUME, volume_bytes);
volume, = struct.unpack("i", volume_bytes)

left, right = split_lr(volume)
left += 20;
right += 20;
volume = join_lr(left, right)

volume_bytes = struct.pack("i", volume)
fcntl.ioctl(fp, ioctl.SOUND_MIXER_WRITE_VOLUME, volume_bytes);

fp.close()
