"""Test cases for sokoban module."""

from unittest import TestCase
from unittest import mock
from unittest.mock import Mock
from unittest.mock import patch
from unittest.mock import mock_open

import unittest
import json

from sokoban import World
from sokoban import GameEngine
from sokoban import GameView
from sokoban import Sokoban
from sokoban import Dir
from sokoban import Key
from sokoban import Tile

import sokoban


class TestWorld(TestCase):
    """Test cases for the World class."""

    @staticmethod
    def make_level_simple():
        return [
            "#########",
            "#.$ @   #",
            "#########"
        ]

    def test_worker_pos(self):
        level = self.make_level_simple()

        world = World(level)

        self.assertEqual(world.worker_pos, [(4, 1)])

    def test_box_pos(self):
        level = self.make_level_simple()

        world = World(level)

        self.assertEqual(world.box_pos, [(2, 1)])

    def test_dock_pos(self):
        level = self.make_level_simple()

        world = World(level)

        self.assertEqual(world.dock_pos, [(1, 1)])

    @staticmethod
    def make_level_with_multiple_boxes():
        return [
            "#########",
            "#.$ @   #",
            "# .$    #",
            "#########"
        ]

    def test_multiple_box_pos(self):
        level = self.make_level_with_multiple_boxes()

        world = World(level)

        self.assertEqual(world.box_pos, [(2, 1), (3, 2)])

    def test_multiple_dock_pos(self):
        level = self.make_level_with_multiple_boxes()

        world = World(level)

        self.assertEqual(world.dock_pos, [(1, 1), (2, 2)])

    @staticmethod
    def make_level_with_box_in_dock():
        return [
            "#########",
            "# * @   #",
            "# .$    #",
            "#########"
        ]

    def test_box_in_dock(self):
        level = self.make_level_with_box_in_dock()

        world = World(level)

        self.assertIn((2, 1), world.box_pos)
        self.assertIn((2, 1), world.dock_pos)

    @staticmethod
    def make_level_with_worker_on_dock():
        return [
            "#########",
            "#.$     #",
            "# +$    #",
            "#########"
        ]

    def test_worker_in_dock(self):
        level = self.make_level_with_worker_on_dock()

        world = World(level)

        self.assertIn((2, 2), world.dock_pos)
        self.assertIn((2, 2), world.worker_pos)

    @staticmethod
    def make_level_with_no_worker():
        return [
            "#########",
            "#.$     #",
            "#########"
        ]

    def test_atleast_one_worker_error(self):
        level = self.make_level_with_no_worker()

        with self.assertRaisesRegex(ValueError, 'worker not found'):
            World(level)

    @staticmethod
    def make_level_with_unbalanced_box_docks():
        return [
            "#########",
            "#.$.  @ #",
            "#########"
        ]

    def test_unbalanced_box_docks_error(self):
        level = self.make_level_with_unbalanced_box_docks()

        with self.assertRaisesRegex(ValueError, "count mismatch"):
            World(level)

    def test_invalid_character(self):
        level = ["ABCD"]

        with self.assertRaisesRegex(ValueError, "character not recognized"):
            World(level)

    @staticmethod
    def make_level_with_no_boxes():
        return [
            "####",
            "# @#",
            "####"
        ]

    def test_level_with_no_boxes(self):
        level = self.make_level_with_no_boxes()

        with self.assertRaisesRegex(ValueError, "boxes not found"):
            World(level)

    def test_get_wall(self):
        level = self.make_level_simple()
        world = World(level)

        tile = world.get((0, 0))

        self.assertEqual(tile.wall, True)

    def test_get_floor(self):
        level = self.make_level_simple()
        world = World(level)

        tile = world.get((1, 1))

        self.assertEqual(tile.wall, False)

    def test_get_dock(self):
        level = self.make_level_simple()
        world = World(level)

        tile = world.get((1, 1))

        self.assertEqual(tile.dock, True)

    def test_get_box(self):
        level = self.make_level_simple()
        world = World(level)

        tile = world.get((2, 1))

        self.assertEqual(tile.box, True)

    def test_get_worker(self):
        level = self.make_level_simple()
        world = World(level)

        tile = world.get((4, 1))

        self.assertEqual(tile.worker, True)

    def test_push_box(self):
        level = self.make_level_simple()
        world = World(level)

        world.push_box((2, 1), (1, 1))

        tile = world.get((1, 1))
        self.assertEqual(tile.box, True)
        self.assertEqual(tile.dock, True)

    def test_move_worker(self):
        level = self.make_level_simple()
        world = World(level)

        world.move_worker((3, 1))

        tile = world.get((3, 1))
        self.assertEqual(tile.worker, True)


class TestGameEngine(TestCase):
    """Test cases for the GameEngine class."""

    @staticmethod
    def make_world_worker_moves_on_floor(worker_x, worker_y):
        world = Mock()
        world.worker_pos = [(worker_x, worker_y)]
        world.get.side_effect = [
            Mock(wall=False, box=False),
            Mock(wall=False, box=False)
        ]
        return world

    def test_move_up(self):
        world = self.make_world_worker_moves_on_floor(2, 2)

        GameEngine.move(Dir.UP, world)

        world.move_worker.assert_called_with((2, 1))

    def test_move_down(self):
        world = self.make_world_worker_moves_on_floor(2, 2)

        GameEngine.move(Dir.DN, world)

        world.move_worker.assert_called_with((2, 3))

    def test_move_left(self):
        world = self.make_world_worker_moves_on_floor(2, 2)

        GameEngine.move(Dir.LT, world)

        world.move_worker.assert_called_with((1, 2))

    def test_move_right(self):
        world = self.make_world_worker_moves_on_floor(2, 2)

        GameEngine.move(Dir.RT, world)

        world.move_worker.assert_called_with((3, 2))

    @staticmethod
    def make_world_worker_moves_into_wall(worker_x, worker_y):
        world = Mock()
        world.worker_pos = [(worker_x, worker_y)]
        world.get.side_effect = [
            Mock(wall=True),
            Mock(wall=True)
        ]
        return world

    def test_move_into_wall(self):
        world = self.make_world_worker_moves_into_wall(2, 2)

        GameEngine.move(Dir.RT, world)

        self.assertFalse(world.move_worker.called)

    @staticmethod
    def make_world_worker_moves_box(worker_x, worker_y):
        world = Mock()
        world.worker_pos = [(worker_x, worker_y)]
        world.get.side_effect = [
            Mock(wall=False, box=True),
            Mock(wall=False, box=False)
        ]
        return world

    def test_move_box(self):
        world = self.make_world_worker_moves_box(2, 2)

        GameEngine.move(Dir.DN, world)

        world.push_box.assert_called_with((2, 3), (2, 4))
        world.move_worker.assert_called_with((2, 3))

    @staticmethod
    def make_world_worker_moves_box_into_wall(worker_x, worker_y):
        world = Mock()
        world.worker_pos = [(worker_x, worker_y)]
        world.get.side_effect = [
            Mock(wall=False, box=True),
            Mock(wall=True, box=False)
        ]
        return world

    def test_move_box_into_wall(self):
        world = self.make_world_worker_moves_box_into_wall(2, 2)

        GameEngine.move(Dir.DN, world)

        self.assertFalse(world.push_box.called)
        self.assertFalse(world.move_worker.called)

    def test_is_game_over_true(self):
        world = Mock()
        world.dock_pos = [(2, 1), (1, 1)]
        world.box_pos = [(1, 1), (2, 1)]

        status = GameEngine.is_game_over(world)

        self.assertTrue(status)

    def test_is_game_over_false(self):
        world = Mock()
        world.dock_pos = [(2, 1), (1, 1)]
        world.box_pos = [(1, 1), (2, 2)]

        status = GameEngine.is_game_over(world)

        self.assertFalse(status)


class TestSokoban(TestCase):
    """Test cases for the Sokoban class."""

    def make_all_mocks(self):
        mock_engine_class = Mock()
        mock_engine = mock_engine_class()
        mock_engine.is_game_over.return_value = False
        patcher = patch("sokoban.GameEngine", mock_engine_class)
        patcher.start()
        self.addCleanup(patcher.stop)

        mock_view_class = Mock()
        mock_view = mock_view_class()
        patcher = patch("sokoban.GameView", mock_view_class)
        patcher.start()
        self.addCleanup(patcher.stop)

        mock_world_class = Mock()
        mock_world = mock_world_class()
        patcher = patch("sokoban.World", mock_world_class)
        patcher.start()
        self.addCleanup(patcher.stop)

        return (mock_engine, mock_view, mock_world)

    def test_quit(self):
        _, mock_view, _ = self.make_all_mocks()
        mock_level0 = Mock()
        mock_levels = [mock_level0]
        game = Sokoban(mock_levels)

        game.handle_key(Key.QUIT)

        mock_view.quit.assert_called_with()

    def test_move_up(self):
        mock_engine, mock_view, mock_world = self.make_all_mocks()
        mock_level0 = Mock()
        mock_levels = [mock_level0]
        game = Sokoban(mock_levels)

        game.handle_key(Key.UP)

        mock_engine.move.assert_called_with(Dir.UP, mock_world)
        mock_view.show_world.assert_called_with(mock_world)

    def test_move_down(self):
        mock_engine, mock_view, mock_world = self.make_all_mocks()
        mock_level0 = Mock()
        mock_levels = [mock_level0]
        game = Sokoban(mock_levels)

        game.handle_key(Key.DOWN)

        mock_engine.move.assert_called_with(Dir.DN, mock_world)
        mock_view.show_world.assert_called_with(mock_world)

    def test_move_left(self):
        mock_engine, mock_view, mock_world = self.make_all_mocks()
        mock_level0 = Mock()
        mock_levels = [mock_level0]
        game = Sokoban(mock_levels)

        game.handle_key(Key.LEFT)

        mock_engine.move.assert_called_with(Dir.LT, mock_world)
        mock_view.show_world.assert_called_with(mock_world)

    def test_move_right(self):
        mock_engine, mock_view, mock_world = self.make_all_mocks()
        mock_level0 = Mock()
        mock_levels = [mock_level0]
        game = Sokoban(mock_levels)

        game.handle_key(Key.RIGHT)

        mock_engine.move.assert_called_with(Dir.RT, mock_world)
        mock_view.show_world.assert_called_with(mock_world)

    def test_skip(self):
        _, mock_view, _ = self.make_all_mocks()
        mock_level0 = Mock()
        mock_levels = [mock_level0]
        game = Sokoban(mock_levels)

        game.handle_key(Key.SKIP)

        self.assertEqual(mock_view.setup_world.call_count, 2)

    def test_game_over(self):
        mock_engine, mock_view, _ = self.make_all_mocks()
        mock_level0 = Mock()
        mock_levels = [mock_level0]
        game = Sokoban(mock_levels)
        mock_engine.is_game_over.return_value = True

        game.handle_key(Key.UP)

        self.assertEqual(mock_view.setup_world.call_count, 2)


class TerminateLoop(Exception):
    pass


class TestGameView(TestCase):
    """Test cases for the GameView class."""

    def make_pygame_mock(self):
        mock_pygame = Mock()

        patcher = patch("sokoban.pygame", mock_pygame)
        patcher.start()
        self.addCleanup(patcher.stop)

        return mock_pygame

    def make_screen_mock(self, mock_pygame):
        mock_screen = Mock()
        mock_pygame.display.set_mode.return_value = mock_screen
        return mock_screen

    def make_image_load_mock(self, mock_pygame):
        mock_pygame.image.load.side_effect = ["#", " ", ".", "$", "@", "*", "+"]

    def test_quit(self):
        mock_pygame = self.make_pygame_mock()
        view = GameView()

        view.quit()

        self.assertTrue(mock_pygame.quit.called)

    @staticmethod
    def make_world_mock(nrows, ncols, tile=None):
        mock_world = Mock()
        mock_world.nrows = nrows
        mock_world.ncols = ncols
        if tile is None:
            tile = Tile(wall=False, box=False, worker=False, dock=False)
        mock_world.get.return_value = tile
        return mock_world

    def test_setup_world(self):
        mock_pygame = self.make_pygame_mock()
        mock_world = self.make_world_mock(1, 1)
        view = GameView()

        view.setup_world(mock_world)

        mock_pygame.display.set_mode.assert_called_with((32, 32))

    def test_show_world(self):
        mock_pygame = self.make_pygame_mock()
        mock_screen = self.make_screen_mock(mock_pygame)
        self.make_image_load_mock(mock_pygame)
        mock_world = self.make_world_mock(1, 1)
        view = GameView()
        view.load_images()
        view.setup_world(mock_world)

        view.show_world(mock_world)

        mock_screen.blit.assert_called_with(" ", (0, 0))

    def test_on_key_press(self):
        mock_pygame = self.make_pygame_mock()
        mock_pygame.event.wait.side_effect = [
            Mock(type=mock_pygame.KEYDOWN, key=mock_pygame.K_UP),
            TerminateLoop
        ]
        mock_game = Mock()
        view = GameView()

        with self.assertRaises(TerminateLoop):
            view.run(mock_game)

        mock_game.handle_key.assert_called_with(Key.UP)

    def test_on_key_press_invalid(self):
        mock_pygame = self.make_pygame_mock()
        mock_pygame.event.wait.side_effect = [
            Mock(type=mock_pygame.KEYDOWN, key=mock_pygame.K_z),
            TerminateLoop
        ]
        mock_game = Mock()
        view = GameView()

        with self.assertRaises(TerminateLoop):
            view.run(mock_game)
        
        self.assertFalse(mock_game.handle_key.called)


class TestLoadLevels(TestCase):
    """Test cases for the load_level function."""

    def test_load_level_success(self):
        level_info = [
            "#########",
            "#.$ @   #",
            "#########"
        ]

        mock_file = mock_open(read_data=json.dumps(level_info))
        patcher = patch("sokoban.xopen", mock_file)
        patcher.start()
        self.addCleanup(patcher.stop)

        got = sokoban.load_levels()

        self.assertEqual(level_info, got)

    def test_load_level_fail(self):
        mock_file = mock_open(read_data="X")
        patcher = patch("sokoban.xopen", mock_file)
        patcher.start()
        self.addCleanup(patcher.stop)

        mock_stderr = Mock()
        patcher = patch("sys.stderr", mock_stderr)
        patcher.start()
        self.addCleanup(patcher.stop)

        with self.assertRaises(SystemExit):
            sokoban.load_levels()


if __name__ == "__main__":
    unittest.main()
