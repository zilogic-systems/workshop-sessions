"""A simple implementation of Sokoban.

The purpose of this module is to provide a sufficiently large
code-base to learn the art of unit testing.
"""

from __future__ import print_function
from collections import namedtuple
from enum import Enum

import json
import sys
import tkinter as tk

Tile = namedtuple("Tile", "wall worker dock box")
Dir = Enum('Dir', 'UP DN LT RT')
Key = Enum('Key', 'UP DOWN LEFT RIGHT QUIT SKIP')


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

        Raises ValueError if parsing level fails.
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
                    raise ValueError(msg)

        if len(self.worker_pos) != 1:
            raise ValueError("worker not found")

        if len(self.dock_pos) != len(self.box_pos):
            raise ValueError("boxes and docks count mismatch")

        if len(self.box_pos) == 0:
            raise ValueError("boxes not found")

        self.nrows = len(level_info)
        self.ncols = max(len(l) for l in level_info)

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
    """Rules engine, decides what is possible within the world.

    Rules:
      * Worker cannot move into a wall
      * Worker can only push 1 box at a time

    Also provides method to check if player has won.
    """

    @staticmethod
    def move(direction, world):
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
        else:  # if direction == Dir.LT:
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

    @staticmethod
    def is_game_over(world):
        """Returns True if all boxes are in docks, False otherwise."""
        for box in world.box_pos:
            if box not in world.dock_pos:
                return False
        return True


class GameView:
    """Interacts with user getting inputs and displaying the world."""
    TILE_SIZE = 32

    def __init__(self):
        self._window = tk.Tk()
        self._window.title("Sokoban!")
        self._canvas = tk.Canvas(self._window)
        self._canvas.pack()
        self._images = {}
        self._event_handler = None

    def load_images(self):
        tile_names = (
            ("wall", Tile(wall=True, worker=False, dock=False, box=False)),
            ("floor", Tile(wall=False, worker=False, dock=False, box=False)),
            ("dock", Tile(dock=True, wall=False, worker=False, box=False)),
            ("box", Tile(box=True, wall=False, worker=False, dock=False)),
            ("worker", Tile(worker=True, wall=False, dock=False, box=False)),
            ("box-docked", Tile(box=True, dock=True, wall=False, worker=False)),
            ("worker-docked", Tile(worker=True, dock=True, wall=False, box=False))
        )

        for name, tile in tile_names:
            self._images[tile] = tk.PhotoImage(file="tiles/{}.ppm".format(name))

    def setup_world(self, world):
        """Sets the size of the game window."""
        width = world.ncols * GameView.TILE_SIZE
        height = world.nrows * GameView.TILE_SIZE
        self._canvas.config(width=width, height=height)

    def show_world(self, world):
        """Updates the tiles on the game window."""
        self._canvas.delete("all")
        for y in range(world.nrows):
            for x in range(world.ncols):
                tile = world.get((x, y))
                sx = x * GameView.TILE_SIZE
                sy = y * GameView.TILE_SIZE
                img = self._images[tile]
                self._canvas.create_image(sx, sy, image=img, tag="all", anchor=tk.NW)

    def quit(self):
        self._window.quit()

    def run(self, event_handler):
        self._event_handler = event_handler
        self._window.bind("<KeyPress>", self._on_key_press)
        self._window.mainloop()

    def _on_key_press(self, event):
        """Maps the key pressed, and invokes key handler callback."""
        key_map = {
            "Up": Key.UP,
            "Left": Key.LEFT,
            "Right": Key.RIGHT,
            "Down": Key.DOWN,
            "q": Key.QUIT,
            "s": Key.SKIP,
        }
        try:
            self._event_handler.handle_key(key_map[event.keysym])
        except KeyError:
            pass


class Sokoban:
    """Game director, ties up engine, world and view."""

    def __init__(self, levels):
        self._levels = levels
        self._current = 0
        self._engine = GameEngine()
        self._view = GameView()
        self._view.load_images()

        self._world = World(self._levels[self._current])
        self._view.setup_world(self._world)
        self._view.show_world(self._world)
        self._view.run(self)

    def _goto_next(self):
        """Increments level and update world."""
        self._current = (self._current + 1) % len(self._levels)
        self._world = World(self._levels[self._current])
        self._view.setup_world(self._world)
        self._view.show_world(self._world)

    def _move(self, direction):
        """Make move and update in view."""
        self._engine.move(direction, self._world)
        self._view.show_world(self._world)

    def handle_key(self, key):
        """Processes a key event.

          * Invoke engine to update the world
          * Invoke view to display the world
          * Check game over and move to next level
        """
        if key == Key.QUIT:
            self._view.quit()
        elif key == Key.UP:
            self._move(Dir.UP)
        elif key == Key.RIGHT:
            self._move(Dir.RT)
        elif key == Key.LEFT:
            self._move(Dir.LT)
        elif key == Key.DOWN:
            self._move(Dir.DN)
        elif key == Key.SKIP:
            self._goto_next()

        if self._engine.is_game_over(self._world):
            self._goto_next()


def load_levels():
    """Returns levels loaded from a JSON file."""
    try:
        return json.load(open("levels.json"))
    except (OSError, IOError, ValueError):
        print("sokoban: loading levels failed!", file=sys.stderr)
        exit(1)

if __name__ == "__main__":
    Sokoban(load_levels())
