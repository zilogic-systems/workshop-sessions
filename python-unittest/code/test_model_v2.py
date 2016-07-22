from sokoban.model import World
from unittest import TestCase

SIMPLE_LEVEL = [
    "#########",
    "#.$ @   #",
    "#########",
]

class WorldTestCase(TestCase):
    def test_rect_world_dimensions(self):
        world = World(SIMPLE_LEVEL)

        self.assertEqual(world.nrows, 3)
        self.assertEqual(world.ncols, 9)
