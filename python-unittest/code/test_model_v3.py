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

### START: tests.py
def test_worker_pos():
    world = World(SIMPLE_LEVEL)
    assert world.worker_pos == [(4, 1)]

def test_single_box_dock():
    world = World(SIMPLE_LEVEL)

    assert world.box_pos == [(2, 1)]
    assert world.dock_pos == [(1, 1)]
### END: tests.py
