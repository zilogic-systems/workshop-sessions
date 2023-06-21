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
