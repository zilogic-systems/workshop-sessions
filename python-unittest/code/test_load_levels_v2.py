import pytest

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

### START: invalid-json.py
def test_load_levels_invalid_json():
    mock_open = Mock()
    mock_open.return_value = StringIO("!!!")
    patcher = patch("sokoban.xopen", mock_open)
    patcher.start()

    pytest.raises(SystemExit, load_levels)

    patcher.stop()
### END: invalid-json.py

### START: os-error.py
def test_load_levels_os_error():
    mock_open = Mock()
    mock_open.side_effect = OSError
    patcher = patch("sokoban.xopen", mock_open)
    patcher.start()

    pytest.raises(SystemExit, load_levels)

    patcher.stop()
### END: os-error.py
