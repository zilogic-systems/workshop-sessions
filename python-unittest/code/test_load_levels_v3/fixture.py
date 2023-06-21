@pytest.fixture
def mock_open(request):
    patcher = patch("sokoban.xopen")
    mock_open = patcher.start()
    request.addfinalizer(patcher.stop)
    return mock_open
