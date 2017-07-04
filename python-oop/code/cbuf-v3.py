"""
Test: Multiple Instances

### START: bundle
>>> cb = new()
>>> init(cb, 4)
>>> cb.tail
0
>>> cb.head
0
>>> cb.bufsize
4
>>> cb.abcd  
Traceback (most recent call last):
  File "<stdin>", line 1, in <module>
AttributeError: 'types.SimpleNamespace' object has no attribute 'abcd'
### END: bundle

### START: multiple
>>> cb1 = new()
>>> cb2 = new()
>>> init(cb1, 4)
>>> add(cb1, "a")
>>> add(cb1, "b")
>>> init(cb2, 4)
>>> add(cb2, "1")
>>> add(cb2, "2")
>>> remove(cb1)
'a'
>>> remove(cb1)
'b'
>>> remove(cb2)
'1'
>>> remove(cb2)
'2'

### END: multiple
"""

### START: cbuf.py
from types import SimpleNamespace as Bundle

### START: new
def new():
    return Bundle()
### END: new

### START: init
def init(cb, size):
    cb.tail = 0
    cb.head = 0
    cb.buf = [None] * size
    cb.bufsize = size
### END: init

def _increment(cb, counter):
    counter += 1
    counter %= cb.bufsize
    return counter

### START: add
def add(cb, data):
    cb.buf[cb.tail] = data

    cb.tail = _increment(cb, cb.tail)
    if cb.tail == cb.head:
        cb.head = _increment(cb, cb.head)
### END: add

### START: remove
def remove(cb):
    if cb.head == cb.tail:
        return None

    data = cb.buf[cb.head]
    cb.head = _increment(cb, cb.head)

    return data
### END: remove
### END: cbuf.py
