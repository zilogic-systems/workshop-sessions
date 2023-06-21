def test_load_levels_os_error():
    mock_open = Mock()
    mock_open.side_effect = OSError
    patcher = patch("sokoban.xopen", mock_open)
    patcher.start()

    pytest.raises(SystemExit, load_levels)

    patcher.stop()
