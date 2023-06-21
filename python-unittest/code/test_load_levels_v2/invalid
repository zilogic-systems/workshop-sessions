def test_load_levels_invalid_json():
    mock_open = Mock()
    mock_open.return_value = StringIO("!!!")
    patcher = patch("sokoban.xopen", mock_open)
    patcher.start()

    pytest.raises(SystemExit, load_levels)

    patcher.stop()
