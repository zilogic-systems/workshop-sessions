class BitArray:
    def __init__(self):
        self._value = 0
    
    def get(self, pos):
        return 1 if self._value & (1 << pos) else 0
    
    def set(self, pos, flag):
        if flag:
            self._value |= (1 << pos)
        else:
            self._value &= ~(1 << pos)
    
    def __repr__(self):
        return "BitArray(0b{:b})".format(self._value)
