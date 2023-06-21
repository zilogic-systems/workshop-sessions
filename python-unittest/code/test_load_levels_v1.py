from unittest.mock import Mock, patch
from io import StringIO

from sokoban import load_levels

def test_load_levels_success():
    mock_open = Mock()
    mock_open.return_value = StringIO("[]")
    patcher = patch("sokoban.xopen", mock_open)
    patcher.start()

    levels = load_levels()

    assert levels == []

    patcher.stop()
