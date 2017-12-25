"""A simple implementation of Sokoban.

The purpose of this module is to provide a sufficiently large
code-base to learn the art of unit testing.
"""

from __future__ import print_function
from collections import namedtuple
from enum import Enum

import sys
import time
import json
import pygame


class LevelInvalidError(Exception):
    """Indicates a parse error in level data."""
    pass


class World:
    """Represents the positions of worker, walls, boxes and docks.

    Walls and docks are fixed for a level. Methods are provided to
    move worker and boxes, around.
    """

    def __init__(self, level_info):
        self.worker_pos = []
        self.box_pos = []
        self.dock_pos = []
        self.wall_pos = []
        self.nrows = 0
        self.ncols = 0
        self._parse(level_info)

    def _parse(self, level_info):
        """Parses the level and initialize initial level state.

        Raises LevelInvalidError if parsing level fails.
        """

        for i, line in enumerate(level_info):
            for j, tile in enumerate(line):
                pos = (j, i)
                #
                # Tile   |   | Dock
                # -------+---+-----
                # Worker | @ | +
                # Floor  |   | .
                # Box    | $ | *
                # Wall   | # | x
                #
                if tile in ('@', '+'):
                    self.worker_pos.append(pos)
                if tile in ('$', '*'):
                    self.box_pos.append(pos)
                if tile in ('.', '*', '+'):
                    self.dock_pos.append(pos)
                if tile == '#':
                    self.wall_pos.append(pos)
                if tile not in ('@', '+', '$', '*', '.', '#', ' ', '\n'):
                    msg = "character not recognized {0}".format(tile)
                    raise LevelInvalidError(msg)

        if len(self.worker_pos) != 1:
            raise LevelInvalidError("worker not found")

        if len(self.dock_pos) != len(self.box_pos):
            raise LevelInvalidError("boxes and docks count mismatch")

        if len(self.box_pos) == 0:
            raise LevelInvalidError("boxes not found")

        self.nrows = len(level_info)
        self.ncols = max(len(l) for l in level_info) - 1

    def get(self, pos):
        """Returns the tile information at specified position."""
        return Tile(wall = (pos in self.wall_pos),
                    worker = (pos in self.worker_pos),
                    dock = (pos in self.dock_pos),
                    box = (pos in self.box_pos))

    def push_box(self, from_pos, to_pos):
        """Moves box from 'from_pos' to 'to_pos'."""
        self.box_pos.remove(from_pos)
        self.box_pos.append(to_pos)

    def move_worker(self, to_pos):
        """Moves worker to specified position."""
        self.worker_pos = [to_pos]


class GameEngine:
    """Rules engine, decides what is possible with the world.

    Rules:
      * Worker cannot move into a wall
      * Worker can only push 1 box at a time

    Also provides method to check if player has won.
    """

    def move(self, direction, world):
        """Move player in a specified direction."""
        x, y = world.worker_pos[0]

        if direction == Dir.UP:
            next_pos = (x, y - 1)
            push_pos = (x, y - 2)
        elif direction == Dir.DN:
            next_pos = (x, y + 1)
            push_pos = (x, y + 2)
        elif direction == Dir.RT:
            next_pos = (x + 1, y)
            push_pos = (x + 2, y)
        elif direction == Dir.LT:
            next_pos = (x - 1, y)
            push_pos = (x - 2, y)

        next_tile = world.get(next_pos)
        push_tile = world.get(push_pos)

        if next_tile.wall:
            return

        if next_tile.box:
            if not push_tile.wall and not push_tile.box:
                world.push_box(next_pos, push_pos)
                world.move_worker(next_pos)
            return

        world.move_worker(next_pos)

    def is_game_over(self, world):
        """Returns True if all boxes are in docks, False otherwise."""

        for dock in world.dock_pos:
            tile = world.get(dock)
            if not tile.box:
                return False
        return True


class GameView:
    """Interacts with user processing inputs and displaying the world."""

    def __init__(self):
        self._tile_size = 32
        self._screen = None
        self._width = None
        self._height = None
        self._images = {}
        self._key_map = {
            pygame.K_UP: Key.UP,
            pygame.K_LEFT: Key.LEFT,
            pygame.K_RIGHT: Key.RIGHT,
            pygame.K_DOWN: Key.DOWN,
            pygame.K_q: Key.QUIT,
        }

        pygame.init()
        pygame.display.set_caption("Sokoban!")
        for name, tile in tiles.items():
            self._images[tile] = self._load_tile(name)

    def set_size(self, ncols, nrows):
        """Sets the screen dimensions."""
        self._width = ncols * self._tile_size
        self._height = nrows * self._tile_size
        self._screen = pygame.display.set_mode((self._width, self._height))

    def show(self, world):
        """Displays the tiles in the world."""
        self._screen.fill((0, 0, 0))

        for y in range(world.nrows):
            for x in range(world.ncols):
                tile = world.get((x, y))
                sx = x * self._tile_size
                sy = y * self._tile_size
                img = self._images[tile]
                self._screen.blit(img, (sx, sy))

        pygame.display.flip()

    def wait_key(self):
        """Waits and returns the key read from the user."""
        while True:
            event = pygame.event.wait()
            if event.type == pygame.QUIT:
                return Key.QUIT
            elif event.type == pygame.KEYDOWN:
                try:
                    return self._key_map[event.key]
                except KeyError:
                    return None

    def _load_tile(self, name):
        """Loads and returns the tile bitmap files."""
        return pygame.image.load("tiles/{0}.bmp".format(name))


Tile = namedtuple("tile", "wall worker dock box")
Dir = Enum('Dir', 'UP DN LT RT')
Key = Enum('Key', 'UP DOWN LEFT RIGHT QUIT')
tiles = {
    "wall": Tile(wall=True, worker=False, dock=False, box=False),
    "floor": Tile(wall=False, worker=False, dock=False, box=False),
    "dock": Tile(dock=True, wall=False, worker=False, box=False),
    "box": Tile(box=True, wall=False, worker=False, dock=False),
    "worker": Tile(worker=True, wall=False, dock=False, box=False),
    "box-docked": Tile(box=True, dock=True, wall=False, worker=False),
    "worker-docked": Tile(worker=True, dock=True, wall=False, box=False)
}


def play(engine, view, world):
    """Runs the game loop.

    while not game over:
        get user input
        feed to game engine, which updates world
        update view with new world state
    """
    
    view.set_size(world.ncols, world.nrows)
    view.show(world)
    while not engine.is_game_over(world):
        inp = view.wait_key()
        if inp == Key.UP:
            engine.move(Dir.UP, world)
        elif inp == Key.DOWN:
            engine.move(Dir.DN, world)
        elif inp == Key.LEFT:
            engine.move(Dir.LT, world)
        elif inp == Key.RIGHT:
            engine.move(Dir.RT, world)
        elif inp == Key.QUIT:
            sys.exit(0)

        view.show(world)
    time.sleep(1)


def main():
    """Sets up and invokes game loop."""

    if len(sys.argv) != 2:
        print("Usage: sokoban <level>", file=sys.stderr)
        sys.exit(1)

    levels = json.load(open("levels.json"))
    nlevel = int(sys.argv[1])
    if nlevel >= len(levels):
        print("sokoban: invalid level", file=sys.stderr)
        sys.exit(1)
        
    view = GameView()
    engine = GameEngine()
    world = World(levels[nlevel])

    play(engine, view, world)


if __name__ == "__main__":
    main()
