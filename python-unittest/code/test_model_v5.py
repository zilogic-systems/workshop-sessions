import pytest
from sokoban import World

SIMPLE_LEVEL = [
    "#########",
    "#.$ @   #",
    "#########",
]

def test_rect_world_dimensions():
    world = World(SIMPLE_LEVEL)

    assert world.nrows == 3
    assert world.ncols == 9

def test_worker_pos():
    world = World(SIMPLE_LEVEL)
    assert world.worker_pos == [(4, 1)]

def test_single_box_dock():
    world = World(SIMPLE_LEVEL)

    assert world.box_pos == [(2, 1)]
    assert world.dock_pos == [(1, 1)]

LARGE_LEVEL = [
    "######## ",
    "#.$ @  ##",
    "#.$     #",
    "#########",
]

def test_nonrect_world_dimenions():
    world = World(LARGE_LEVEL)
    assert world.nrows == 4
    assert world.ncols == 9

def test_multiple_box_dock():
    world = World(LARGE_LEVEL)
    assert world.box_pos == [(2, 1), (2, 2)]
    assert world.dock_pos == [(1, 1), (1, 2)]

### START: test1.py
def test_invalid_character_error():
    level = [
        "########!",
        "#.$     #",
        "#########",
    ]

    pytest.raises(ValueError, World, level)
### END: test1.py

### START: test2.py
def test_invalid_character_error():
    level = [
        "########!",
        "#.$     #",
        "#########",
    ]

    excinfo = pytest.raises(ValueError, World, level)
    assert excinfo.match("character")
### END: test2.py

### START: test3.py
def test_no_worker_error():
    level = [
        "#########",
        "#.$     #",
        "#########",
    ]
    excinfo = pytest.raises(ValueError, World, level)
    assert excinfo.match("worker")
### END: test3.py
