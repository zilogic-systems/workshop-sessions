"""
### START: single
>>> cb = CBuf()
>>> cb.init(4)
>>> cb.add("a")
>>> cb.add("b")
>>> cb.remove()
'a'
>>> cb.remove()
'b'

### END: single

### START: multiple
>>> cb1 = CBuf()
>>> cb2 = CBuf()
>>> cb1.init(4)
>>> cb1.add("a")
>>> cb1.add("b")
>>> cb2.init(4)
>>> cb2.add("1")
>>> cb2.add("2")
>>> cb1.remove()
'a'
>>> cb1.remove()
'b'
>>> cb2.remove()
'1'
>>> cb2.remove()
'2'

### END: multiple
"""

### START: class1
class CBuf:
    def init(cb, size):
        cb.tail = 0
        cb.head = 0
        cb.buf = [None] * size
        cb.bufsize = size
### END: class1

    def _increment(cb, counter):
        counter += 1
        counter %= cb.bufsize
        return counter

### START: class2
    def add(cb, data):
        cb.buf[cb.tail] = data

        cb.tail = cb._increment(cb.tail)
        if cb.tail == cb.head:
            cb.head = cb._increment(cb.head)
### END: class2

### START: class3
    def remove(cb):
        if cb.head == cb.tail:
            return None

        data = cb.buf[cb.head]
        cb.head = cb._increment(cb.head)
        return data
### END: class3
