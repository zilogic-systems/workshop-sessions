from .utils import Position
from .utils import Tile


class GameState:
    def __init__(self, level):
        self.world = World(level)
        self.moves = []


class World:
    def __init__(self, level):
        self._maze = []
        self.worker_pos = None
        self.box_pos = set()
        self.docks = set()
        self.nrows = 0
        self.ncols = 0
        self.pushes = 0
        self._read_from_file(level)

    def _read_from_file(self, level):
        self._maze = []
        for i, line in enumerate(level):
            row = []
            for j, tile in enumerate(line):
                pos = Position(j, i)

                if tile == '@':
                    self.worker_pos = pos
                    tile = Tile.FLOOR

                elif tile == '$':
                    self.box_pos.add(pos)
                    tile = Tile.FLOOR

                elif tile == '.':
                    self.docks.add(pos)
                    tile = Tile.DOCK

                elif tile == '*':
                    self.box_pos.add(pos)
                    self.docks.add(pos)
                    tile = Tile.DOCK

                elif tile == "+":
                    self.docks.add(pos)
                    self.worker_pos = pos
                    tile = Tile.DOCK

                elif tile == '#':
                    tile = Tile.WALL

                elif tile == ' ':
                    tile = Tile.FLOOR

                else:
                    continue

                row.append(tile)

            self._maze.append(row)

        self.nrows = len(self._maze)
        self.ncols = max(map(len, self._maze))

    def get(self, pos):
        if pos == self.worker_pos:
            return Tile.WORKER
        elif pos in self.box_pos and pos in self.docks:
            return Tile.BOX_DOCKED
        elif pos in self.box_pos:
            return Tile.BOX
        else:
            try:
                return self._maze[pos.y][pos.x]
            except IndexError:
                return None

    def push_box(self, from_pos, to_pos):
        self.box_pos.remove(from_pos)
        self.box_pos.add(to_pos)
        self.pushes += 1
