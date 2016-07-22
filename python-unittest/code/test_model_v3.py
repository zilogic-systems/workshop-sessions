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

### START: tests.py
    def test_worker_pos(self):
        world = World(SIMPLE_LEVEL)
        self.assertEqual(world.worker_pos, (4, 1))

    def test_single_box_dock(self):
        world = World(SIMPLE_LEVEL)
        self.assertEqual(world.box_pos, {(2, 1)})
        self.assertEqual(world.dock_pos, {(1, 1)})
### END: tests.py
