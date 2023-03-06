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
