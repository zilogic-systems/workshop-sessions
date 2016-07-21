import sys
import atexit
import copy
import os
import time
from collections import namedtuple

import pygame

Position = namedtuple("Position", "x y")

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


class GameState:
    def __init__(self, world, moves):
        self.world = world
        self.moves = moves


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


class GameView:
    def __init__(self, gl):
        self.gl = gl
        self._tile_size = gl.tile_size
        self._screen = None
        self._width = None
        self._height = None
        self._images = {}
        for tile in range(Tile.MAX):
            self._images[tile] = self.gl.load_tile(tile)

    def _get_line_height(self):
        _, dim = self.gl.render_string("|")
        width, height = dim
        return height

    def set_size(self, ncols, nrows):
        line_height = self._get_line_height()
        self._width = ncols * self._tile_size
        self._height = nrows * self._tile_size + line_height * 2

        self._screen = self.gl.resize(self._width, self._height)

    def _draw_status_line(self, world, moves):
        x = 0
        y = (world.nrows * self._tile_size)
        img, _ = self.gl.render_string("MOVES  PUSHES")
        self.gl.draw_image(self._screen, x, y, img)

        y += self._get_line_height()
        img, _ = self.gl.render_string(" {0:04}     {1:04}".format(len(moves), world.pushes))
        self.gl.draw_image(self._screen, x, y, img)

    def show(self, state):
        self.gl.clear(self._screen)
        world = state.world
        moves = state.moves

        for y in range(world.nrows):
            for x in range(world.ncols):
                tile = world.get(Position(x, y))
                if tile == None:
                    tile = Tile.WALL

                sx = x * self._tile_size
                sy = y * self._tile_size
                img = self._images[tile]
                self.gl.draw_image(self._screen, sx, sy, img)

        self._draw_status_line(world, moves)
        self.gl.update(self._screen)
                
    def show_msgbox(self, text):
        self.gl.clear(self._screen)

        img, dim = self.gl.render_string(text)
        string_width, string_height = dim

        x = self._width / 2 - string_width / 2
        y = self._height / 2 - string_height / 2
        self.gl.draw_image(self._screen, x, y, img)

        self.gl.update(self._screen)
        time.sleep(2)

    def wait_key(self):
        while True:
            key = self.gl.read_key()
            if key is not None:
                return key


class PyGameGL:
    def __init__(self):
        pygame.init()
        pygame.display.set_caption("Sokoban!")

        self.tile_size = 32

        self._tile_map = {
            Tile.WORKER: "worker",
            Tile.BOX: "box",
            Tile.BOX_DOCKED: "box-docked",
            Tile.WALL: "wall",
            Tile.DOCK: "dock",
            Tile.FLOOR: "floor",
        }
        self._key_map = {
            pygame.K_UP: Key.UP,
            pygame.K_LEFT: Key.LEFT,
            pygame.K_RIGHT: Key.RIGHT,
            pygame.K_DOWN: Key.DOWN,
            pygame.K_q: Key.QUIT,
            pygame.K_BACKSPACE: Key.UNDO,
            pygame.K_s: Key.SKIP,
            pygame.K_SPACE: Key.OK,
            pygame.K_r: Key.RESET,
        }
        self._font = pygame.font.Font("atari.ttf", 12)

    def resize(self, width, height):
        return pygame.display.set_mode((width, height))

    def load_tile(self, tile):
        tile_name = self._tile_map[tile]
        return pygame.image.load("tiles/{0}.bmp".format(tile_name))

    def draw_image(self, screen, x, y, image):
        screen.blit(image, (x, y))

    def render_string(self, string):
        surface = self._font.render(string, 1, (200, 200, 200), (0, 0, 0))
        return surface, (surface.get_width(), surface.get_height())

    def clear(self, screen):
        screen.fill((0, 0, 0))

    def update(self, screen):
        pygame.display.flip()

    def read_key(self):
        event = pygame.event.wait()
        if event.type == pygame.QUIT:
            return Key.QUIT
        elif event.type == pygame.KEYDOWN:
            try:
                return self._key_map[event.key]
            except KeyError:
                return None


class GameEngine:
    def _is_floor(self, tile):
        return tile in (Tile.FLOOR, Tile.DOCK)

    def _is_box(self, tile):
        return tile in (Tile.BOX, Tile.BOX_DOCKED)

    def move(self, direction, state):
        saved_world = copy.deepcopy(state.world)
        moved = self._move(direction, state.world)
        if moved:
            state.moves.append(saved_world)

    def _move(self, direction, world):
        pos = world.worker_pos

        if direction == Dir.UP:
            next_pos = Position(pos.x, pos.y - 1)
            push_pos = Position(pos.x, pos.y - 2)
        elif direction == Dir.DN:
            next_pos = Position(pos.x, pos.y + 1)
            push_pos = Position(pos.x, pos.y + 2)
        elif direction == Dir.RT:
            next_pos = Position(pos.x + 1, pos.y)
            push_pos = Position(pos.x + 2, pos.y)
        elif direction == Dir.LT:
            next_pos = Position(pos.x - 1, pos.y)
            push_pos = Position(pos.x - 2, pos.y)

        next_tile = world.get(next_pos)
        push_tile = world.get(push_pos)

        if next_tile is None:
            return None
        elif next_tile == Tile.WALL:
            return False
        elif self._is_box(next_tile):
            if self._is_floor(push_tile):
                world.push_box(next_pos, push_pos)
                world.worker_pos = next_pos
                return True
            else:
                return False
        elif self._is_floor(next_tile):
            world.worker_pos = next_pos
            return True

    def undo(self, state):
        try:
            state.world = moves.pop()
        except IndexError:
            pass

    def reset(self, state):
        try:
            while True:
                state.world = state.moves.pop()
        except IndexError:
            pass

    def is_game_over(self, state):
        for dock in state.world.docks:
            if state.world.get(dock) != Tile.BOX_DOCKED:
                return False
        return True


class GameController:
    def _react(self, view, engine, state):
        while not engine.is_game_over(state):
            inp = view.wait_key()
            if inp == Key.UP:
                engine.move(Dir.UP, state)
            elif inp == Key.DOWN:
                engine.move(Dir.DN, state)
            elif inp == Key.LEFT:
                engine.move(Dir.LT, state)
            elif inp == Key.RIGHT:
                engine.move(Dir.RT, state)
            elif inp == Key.UNDO:
                engine.undo(state)
            elif inp == Key.RESET:
                engine.reset(state)
            elif inp == Key.SKIP:
                break
            elif inp == Key.QUIT:
                sys.exit(0)

            view.show(state)
    
    def _play_level(self, view, level):
        world = World(level)
        engine = GameEngine()
        state = GameState(world, moves=[])

        view.set_size(world.ncols, world.nrows)
        view.show(state)

        self._react(view, engine, state)

        if engine.is_game_over(state):
            time.sleep(1)
            view.show_msgbox("LEVEL COMPLETE!")


    def play(self, view, levels):
        for level in levels:
            self._play_level(view, level)


def _read_levels():
    levels = []
    curr_level = []
    for line in open("levels.txt"):
        try:
            if line[0] == ";":
                levels.append(curr_level)
                curr_level = []
            else:
                curr_level.append(line)
        except IndexError:
            pass

    return levels


def main():
    gl = PyGameGL()
    view = GameView(gl)
    levels = _read_levels()
    ctl = GameController()
    ctl.play(view, levels)


if __name__ == "__main__":
    main()
