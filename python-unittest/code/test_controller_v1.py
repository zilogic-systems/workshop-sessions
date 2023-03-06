from unittest.mock import Mock
from sokoban import GameEngine

def test_game_is_over_true():
    # Arrange
    engine = GameEngine()
    world = Mock()
    world.box_pos = [(1, 1), (1, 2)]
    world.dock_pos = [(1, 1), (1, 2)]
    # Act
    result = engine.is_game_over(world)
    # Assert
    assert result == True
