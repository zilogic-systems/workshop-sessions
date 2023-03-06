from sokoban import World

level = [ 
    "#########",
    "#.$ @   #",
    "#########",
]

world = World(level)
print(world.nrows)      # 3
print(world.ncols)      # 9
print(world.worker_pos) # [(4, 1)]
print(world.box_pos)    # [(2, 1)]
print(world.dock_pos)   # [(1, 1)]
