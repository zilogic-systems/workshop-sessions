class CBuf:
    def __init__(cb, size):
        cb.tail = 0
        cb.head = 0
        cb.buf = [None] * size
        cb.bufsize = size

    def _increment(cb, counter):
        counter += 1
        counter %= cb.bufsize
        return counter

    def add(cb, data):
        cb.buf[cb.tail] = data

        cb.tail = cb._increment(cb.tail)
        if cb.tail == cb.head:
            cb.head = cb._increment(cb.head)

    def remove(cb):
        if cb.head == cb.tail:
            return None

        data = cb.buf[cb.head]
        cb.head = cb._increment(cb.head)

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
