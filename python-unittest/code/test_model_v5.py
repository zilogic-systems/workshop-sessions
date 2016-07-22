from sokoban.model import World
from sokoban.model import LevelInvalidError
from unittest import TestCase

SIMPLE_LEVEL = [
    "#########",
    "#.$ @   #",
    "#########",
]

LARGE_LEVEL = [
    "######## ",
    "#.$ @  ##",
    "#.$     #",
    "#########",
]

class WorldTestCase(TestCase):
    def test_rect_world_dimensions(self):
        world = World(SIMPLE_LEVEL)

        self.assertEqual(world.nrows, 3)
        self.assertEqual(world.ncols, 9)

    def test_nonrect_world_dimenions(self):
        world = World(LARGE_LEVEL)

        self.assertEqual(world.nrows, 4)
        self.assertEqual(world.ncols, 9)

    def test_worker_pos(self):
        world = World(SIMPLE_LEVEL)
        self.assertEqual(world.worker_pos, (4, 1))

    def test_single_box_dock(self):
        world = World(SIMPLE_LEVEL)
        self.assertEqual(world.box_pos, {(2, 1)})
        self.assertEqual(world.dock_pos, {(1, 1)})

    def test_multiple_box_dock(self):
        world = World(LARGE_LEVEL)
        self.assertEqual(world.box_pos, {(2, 1), (2, 2)})
        self.assertEqual(world.dock_pos, {(1, 1), (1, 2)})

    def test_invalid_character_error(self):
        level = [
            "########!",
            "#.$     #",
            "#########",
        ]

        self.assertRaisesRegex(LevelInvalidError, "character", World, level)

    def test_no_worker_error(self):
        level = [
            "#########",
            "#.$     #",
            "#########",
        ]

        self.assertRaises(LevelInvalidError, "worker", World, level)



                         
