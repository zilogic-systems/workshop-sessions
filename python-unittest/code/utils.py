from sokoban import Tile
from sokoban import Dir
from sokoban import World
from sokoban import GameEngine
from sokoban import GameView


SIMPLE_LEVEL = [
    "#########",
    "#.$ @   #",
    "#########",
]

def display_world(world):
    tile_map = {
        Tile(wall=True, worker=False, dock=False, box=False): "#", 
        Tile(wall=False, worker=False, dock=False, box=False): " ", 
        Tile(dock=True, wall=False, worker=False, box=False): ".", 
        Tile(box=True, wall=False, worker=False, dock=False): "$", 
        Tile(worker=True, wall=False, dock=False, box=False): "@", 
        Tile(box=True, dock=True, wall=False, worker=False): "*", 
        Tile(worker=True, dock=True, wall=False, box=False): "+", 
    }

    print("  ", end="")
    for col in range(world.ncols):
        print(col, end="")
    print()

    for row in range(world.nrows):
        print(row, "", end="")
        for col in range(world.ncols):
            tile = world.get((col, row))
            print(tile_map[tile], end="")
        print()
