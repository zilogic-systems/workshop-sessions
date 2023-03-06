from unittest.mock import patch
from sokoban import GameView

def test_set_window_title():
    patcher = patch("sokoban.pygame")
    mock_pygame = patcher.start()
    
    view = GameView()

    mock_pygame.display.set_caption.assert_called_with("Sokoban!")

    patcher.stop()
