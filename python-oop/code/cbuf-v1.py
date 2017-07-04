"""
Test 1: Simple

### START: simple
>>> init(4)
>>> add("a")
>>> add("b")
>>> remove()
'a'
>>> remove()
'b'
>>>

### END: simple

Test 2: Empty

### START: empty
>>> init(4)
>>> remove()
>>>

### END: empty

Test 3: Wrap Around

### START: wrap
>>> init(4)
>>> add("a")
>>> add("b")
>>> add("c")
>>> add("d")
>>> for i in range(3):
...     remove()
...
'b'
'c'
'd'

### END: wrap

Test 4: Remove all

### START: remove-all
>>> init(4)
>>> add("a")
>>> add("b")
>>> remove()
'a'
>>> remove()
'b'
>>> remove()

### END: remove-all
"""

### START: cbuf.py
### START: init
def init(size):
    global tail, head, buf, bufsize
    
    tail = 0
    head = 0
    buf = [None] * size
    bufsize = size
### END: init

def _increment(counter):
    counter += 1
    counter %= bufsize
    return counter

### START: add
def add(data):
    global tail, head, buf

    buf[tail] = data

    tail = _increment(tail)
    if tail == head:
        head = _increment(head)
### END: add

### START: remove
def remove():
    global tail, head, buf

    if head == tail:
        return None

    data = buf[head]
    head = _increment(head)

    return data
### END: remove

### END: cbuf.py
