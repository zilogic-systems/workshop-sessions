from .utils import Tile
from copy import deepcopy
from copy import copy


class LevelInvalidError(Exception):
    pass


class GameState:
    def __init__(self, level):
        self.world = World(level)
        self.moves = []


class World:
    def __init__(self, level=None):
        self._map = []
        self.worker_pos = None
        self.box_pos = set()
        self.dock_pos = set()
        self.nrows = 0
        self.ncols = 0
        self.pushes = 0

        if level is not None:
            self._parse(level)

    def _parse(self, level):
        self._map = []
        for i, line in enumerate(level):
            row = []
            for j, tile in enumerate(line):
                pos = (j, i)

                if tile == '@':
                    self.worker_pos = pos
                    tile = Tile.FLOOR

                elif tile == '$':
                    self.box_pos.add(pos)
                    tile = Tile.FLOOR

                elif tile == '.':
                    self.dock_pos.add(pos)
                    tile = Tile.DOCK

                elif tile == '*':
                    self.box_pos.add(pos)
                    self.dock_pos.add(pos)
                    tile = Tile.DOCK

                elif tile == "+":
                    self.dock_pos.add(pos)
                    self.worker_pos = pos
                    tile = Tile.DOCK

                elif tile == '#':
                    tile = Tile.WALL

                elif tile == ' ':
                    tile = Tile.FLOOR

                elif tile == '\n':
                    continue

                else:
                    msg = "character not recognized {0}".format(tile)
                    raise LevelInvalidError(msg)

                row.append(tile)

            self._map.append(row)

        if self.worker_pos is None:
            raise LevelInvalidError("worker not found")

        if len(self.dock_pos) != len(self.box_pos):
            raise LevelInvalidError("boxes and docks count mismatch")

        if len(self.box_pos) is 0:
            raise LevelInvalidError("boxes not found")
        self.nrows = len(self._map)
        self.ncols = max(map(len, self._map))

    def get(self, pos):
        if pos == self.worker_pos:
            return Tile.WORKER
        elif pos in self.box_pos and pos in self.dock_pos:
            return Tile.BOX_DOCKED
        elif pos in self.box_pos:
            return Tile.BOX
        else:
            try:
                x, y = pos
                return self._map[y][x]
            except IndexError:
                return None

    def push_box(self, from_pos, to_pos):
        self.box_pos.remove(from_pos)
        self.box_pos.add(to_pos)
        self.pushes += 1

    def move_worker(self, to_pos):
        self.worker_pos = to_pos

    def copy(self):
        new_world = World()
        new_world._map = deepcopy(self._map)
        new_world.worker_pos = self.worker_pos
        new_world.box_pos = copy(self.box_pos)
        new_world.dock_pos = copy(self.dock_pos)
        new_world.nrows = self.nrows
        new_world.ncols = self.ncols
        new_world.pushes = self.pushes
        return new_world
