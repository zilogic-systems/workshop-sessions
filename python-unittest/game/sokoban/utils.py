from collections import namedtuple

class Tile:
    WALL = 0
    FLOOR = 1
    DOCK = 2
    BOX = 3
    WORKER = 4
    BOX_DOCKED = 5
    MAX = 6


class Dir:
    UP = 0
    DN = 1
    LT = 2
    RT = 3


class Key:
    UP = 0
    DOWN = 1
    LEFT = 2
    RIGHT = 3
    SKIP = 4
    UNDO = 5
    QUIT = 6
    OK = 7
    RESET = 8
