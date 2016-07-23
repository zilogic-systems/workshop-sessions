import pygame
import time

from .utils import Tile
from .utils import Key


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

    def _draw_status_line(self, world, history):
        x = 0
        y = (world.nrows * self._tile_size)
        img, _ = self.gl.render_string("MOVES  PUSHES")
        self.gl.draw_image(self._screen, x, y, img)

        y += self._get_line_height()
        img, _ = self.gl.render_string(" {0:04}     {1:04}".format(len(history), world.pushes))
        self.gl.draw_image(self._screen, x, y, img)

    def show(self, state):
        self.gl.clear(self._screen)
        world = state.world
        history = state.history

        for y in range(world.nrows):
            for x in range(world.ncols):
                tile = world.get((x, y))
                if tile == None:
                    tile = Tile.WALL

                sx = x * self._tile_size
                sy = y * self._tile_size
                img = self._images[tile]
                self.gl.draw_image(self._screen, sx, sy, img)

        self._draw_status_line(world, history)
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

    ### START: resize.py
    def resize(self, width, height):
        return pygame.display.set_mode((width, height))
    ### END: resize.py

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

    ### START: read-key.py
    def read_key(self):
        event = pygame.event.wait()
        if event.type == pygame.QUIT:
            return Key.QUIT
        elif event.type == pygame.KEYDOWN:
            try:
                return self._key_map[event.key]
            except KeyError:
                return None
    ### END: read-key.py
