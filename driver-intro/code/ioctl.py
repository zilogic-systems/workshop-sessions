import ioctl_util

CDROMEJECT = 0x5309

RTC_RD_TIME = ioctl_util._IOR(ord("p"), 0x09, "iiiiiiiii")

SOUND_MIXER_READ_VOLUME = ioctl_util._IOR(ord("M"), 0, "i")
SOUND_MIXER_WRITE_VOLUME = ioctl_util._IOWR(ord("M"), 0, "i")
