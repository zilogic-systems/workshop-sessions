"""
### START: usage
>>> cb = CBuf(4)
>>> cb.add("a")
>>> cb.add("b")
>>> cb.remove()
'a'
>>> cb.remove()
'b'

### END: usage
"""

### START: cbuf.py
### START: class1
class CBuf:
    def __init__(self, size):
        self.tail = 0
        self.head = 0
        self.buf = [None] * size
        self.bufsize = size
### END: class1

    def _increment(self, counter):
        counter += 1
        counter %= self.bufsize
        return counter

### START: class2
    def add(self, data):
        self.buf[self.tail] = data

        self.tail = self._increment(self.tail)
        if self.tail == self.head:
            self.head = self._increment(self.head)
### END: class2

### START: class3
    def remove(self):
        if self.head == self.tail:
            return None

        data = self.buf[self.head]
        self.head = self._increment(self.head)

        return data
### END: class3
### END: cbuf.py
