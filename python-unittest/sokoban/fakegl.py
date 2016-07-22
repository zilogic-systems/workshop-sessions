class FakeGL:
    def __init__(self, keys):
        self.grid = None
        self.tile_size = 1
        self._keys = keys
        self._tile_map = {
            Tile.WORKER: "@",
            Tile.BOX: "$",
            Tile.BOX_DOCKED: "*",
            Tile.WALL: "#",
            Tile.DOCK: ".",
            Tile.FLOOR: " ",
        }

    def resize(self, width, height):
        self.grid = []
        for i in range(height):
            self.grid.append([None] * width)
        return self.grid

    def load_tile(self, tile):
        return self._tile_map[tile]

    def draw_image(self, screen, x, y, image):
        try:
            for i, ch in enumerate(image):
                screen[y][x + i] = ch
        except IndexError:
            pass

    def render_string(self, string):
        return (string, (len(string), 1))

    def clear(self, screen):
        height = len(screen)
        width = len(screen[0])
        
        for i in range(height):
            for j in range(width):
                screen[i][j] = None

    def update(self, screen):
        pass

    def read_key(self):
        try:
            return self._keys.pop(0)
        except IndexError:
            return Key.QUIT
class FakeGL:
    def __init__(self, keys):
        self.grid = None
        self.tile_size = 1
        self._keys = keys
        self._tile_map = {
            Tile.WORKER: "@",
            Tile.BOX: "$",
            Tile.BOX_DOCKED: "*",
            Tile.WALL: "#",
            Tile.DOCK: ".",
            Tile.FLOOR: " ",
        }

    def resize(self, width, height):
        self.grid = []
        for i in range(height):
            self.grid.append([None] * width)
        return self.grid

    def load_tile(self, tile):
        return self._tile_map[tile]

    def draw_image(self, screen, x, y, image):
        try:
            for i, ch in enumerate(image):
                screen[y][x + i] = ch
        except IndexError:
            pass

    def render_string(self, string):
        return (string, (len(string), 1))

    def clear(self, screen):
        height = len(screen)
        width = len(screen[0])
        
        for i in range(height):
            for j in range(width):
                screen[i][j] = None

    def update(self, screen):
        pass

    def read_key(self):
        try:
            return self._keys.pop(0)
        except IndexError:
            return Key.QUIT
