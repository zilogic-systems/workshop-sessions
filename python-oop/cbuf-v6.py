class CBuf:
    def __init__(self, size):
        self.tail = 0
        self.head = 0
        self.buf = [None] * size
        self.bufsize = size

    def _increment(self, counter):
        counter += 1
        counter %= self.bufsize
        return counter

    def add(self, data):
        self.buf[self.tail] = data

        self.tail = self._increment(self.tail)
        if self.tail == self.head:
            self.head = self._increment(self.head)

    def remove(cb):
        if self.head == self.tail:
            return None

        data = self.buf[self.head]
        self.head = self._increment(self.head)

        return data

def main():
    cb1 = CBuf(4)
    cb2 = CBuf(4)

    cb1.add("a")
    cb1.add("b")

    cb2.add("1")
    cb2.add("2")

    print cb1.remove()
    print cb1.remove()

    print cb2.remove()
    print cb2.remove()

if __name__ == "__main__":
    main()
