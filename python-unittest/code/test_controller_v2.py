import pytest

from unittest.mock import Mock
from sokoban import GameEngine

### START: test.py
def test_game_is_over_false():
    # Arrange
    engine = GameEngine()
    world = Mock()
    world.box_pos = [(1, 1), (2, 2)]
    world.dock_pos = [(1, 1), (1, 2)]
    # Act
    result = engine.is_game_over(world)
    # Assert
    assert result == False
### END: test.py
