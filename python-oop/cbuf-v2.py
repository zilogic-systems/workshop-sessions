def new():
    return {}

def init(cb, size):
    cb["tail"] = 0
    cb["head"] = 0
    cb["buf"] = [None] * size
    cb["bufsize"] = size

def _increment(cb, counter):
    counter += 1
    counter %= cb["bufsize"]
    return counter

def add(cb, data):
    tail = cb["tail"]
    cb["buf"][tail] = data

    cb["tail"] = _increment(cb, cb["tail"])
    if cb["tail"] == cb["head"]:
        cb["head"] = _increment(cb, cb["head"])

def remove(cb):
    if cb["head"] == cb["tail"]:
        return None

    head = cb["head"]
    data = cb["buf"][head]
    cb["head"] = _increment(cb, cb["head"])

    return data

def main():
    cb1 = new()
    cb2 = new()

    init(cb1, 4)
    add(cb1, "a")
    add(cb1, "b")

    init(cb2, 4)
    add(cb2, "1")
    add(cb2, "2")

    print cb1
    print cb2

    print remove(cb1)
    print remove(cb1)

    print remove(cb2)
    print remove(cb2)

if __name__ == "__main__":
    main()
