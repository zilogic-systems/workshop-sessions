def init(size):
    global tail, head, buf, bufsize
    
    tail = 0
    head = 0
    buf = [None] * size
    bufsize = size

def _increment(counter):
    counter += 1
    counter %= bufsize
    return counter

def add(data):
    global tail, head, buf

    buf[tail] = data

    tail = _increment(tail)
    if tail == head:
        head = _increment(head)

def remove():
    global tail, head, buf

    if head == tail:
        return None

    data = buf[head]
    head = _increment(head)

    return data

def main():
    print "##"
    print "## Test 1: Simple"
    print "##"

    init(4)

    add("a")
    add("b")

    print remove()
    print remove()

    print "##"
    print "## Test 2: Empty"
    print "##"

    init(4)

    print remove()

    print "##"
    print "## Test 3: Wrap Around"
    print "##"

    init(4)
    add("a")
    add("b")
    add("c")
    add("d")

    for i in range(4):
        print remove()

    print "##"
    print "## Test 4: Remove all"
    print "##"

    init(4)
    add("a")
    add("b")
    remove()
    remove()

    print remove()

