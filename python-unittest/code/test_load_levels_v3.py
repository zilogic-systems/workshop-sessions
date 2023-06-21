import pytest

from unittest.mock import Mock, patch
from io import StringIO

from sokoban import load_levels

### START: fixture.py
@pytest.fixture
def mock_open(request):
    patcher = patch("sokoban.xopen")
    mock_open = patcher.start()
    request.addfinalizer(patcher.stop)
    return mock_open
### END: fixture.py

### START: test-cases.py
def test_load_levels_success(mock_open):
    mock_open.return_value = StringIO("[]")
    levels = load_levels()
    assert levels == []

def test_load_levels_invalid_json(mock_open):
    mock_open.return_value = StringIO("!!!")
    pytest.raises(SystemExit, load_levels)

def test_load_levels_os_error(mock_open):
    mock_open.side_effect = OSError
    pytest.raises(SystemExit, load_levels)
### END: test-cases.py
