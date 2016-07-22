from unittest import TestCase
from mock import Mock
from sokoban.controller import GameEngine
from sokoban.utils import Dir
from sokoban.utils import Tile

### START: test.py
class GameEngineTestCase(TestCase):
    def test_worker_can_move_on_floor(self):
        # Arrange
        engine = GameEngine()
        state = Mock()
        state.world.worker_pos = (1, 1)
        state.world.get.side_effect = [Tile.FLOOR, Tile.FLOOR]
        # Act
        engine.move(Dir.RT, state)
        # Assert
        state.world.move_worker.assert_called_with((2, 1))
### END: test.py
