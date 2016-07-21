import copy
import sys
import time


from .model import GameState
from .utils import Tile
from .utils import Key
from .utils import Dir
from .utils import Position


class GameEngine:
    def _is_floor(self, tile):
        return tile in (Tile.FLOOR, Tile.DOCK)

    def _is_box(self, tile):
        return tile in (Tile.BOX, Tile.BOX_DOCKED)

    def move(self, direction, state):
        saved_world = copy.deepcopy(state.world)
        moved = self._move(direction, state.world)
        if moved:
            state.moves.append(saved_world)

    def _move(self, direction, world):
        pos = world.worker_pos

        if direction == Dir.UP:
            next_pos = Position(pos.x, pos.y - 1)
            push_pos = Position(pos.x, pos.y - 2)
        elif direction == Dir.DN:
            next_pos = Position(pos.x, pos.y + 1)
            push_pos = Position(pos.x, pos.y + 2)
        elif direction == Dir.RT:
            next_pos = Position(pos.x + 1, pos.y)
            push_pos = Position(pos.x + 2, pos.y)
        elif direction == Dir.LT:
            next_pos = Position(pos.x - 1, pos.y)
            push_pos = Position(pos.x - 2, pos.y)

        next_tile = world.get(next_pos)
        push_tile = world.get(push_pos)

        if next_tile is None:
            return None
        elif next_tile == Tile.WALL:
            return False
        elif self._is_box(next_tile):
            if self._is_floor(push_tile):
                world.push_box(next_pos, push_pos)
                world.worker_pos = next_pos
                return True
            else:
                return False
        elif self._is_floor(next_tile):
            world.worker_pos = next_pos
            return True

    def undo(self, state):
        try:
            state.world = moves.pop()
        except IndexError:
            pass

    def reset(self, state):
        try:
            while True:
                state.world = state.moves.pop()
        except IndexError:
            pass

    def is_game_over(self, state):
        for dock in state.world.dock_pos:
            if state.world.get(dock) != Tile.BOX_DOCKED:
                return False
        return True


class GameController:
    def _react(self, view, engine, state):
        while not engine.is_game_over(state):
            inp = view.wait_key()
            if inp == Key.UP:
                engine.move(Dir.UP, state)
            elif inp == Key.DOWN:
                engine.move(Dir.DN, state)
            elif inp == Key.LEFT:
                engine.move(Dir.LT, state)
            elif inp == Key.RIGHT:
                engine.move(Dir.RT, state)
            elif inp == Key.UNDO:
                engine.undo(state)
            elif inp == Key.RESET:
                engine.reset(state)
            elif inp == Key.SKIP:
                break
            elif inp == Key.QUIT:
                sys.exit(0)

            view.show(state)
    
    def _play_level(self, view, level):
        engine = GameEngine()
        state = GameState(level)

        world = state.world
        view.set_size(world.ncols, world.nrows)
        view.show(state)

        self._react(view, engine, state)

        if engine.is_game_over(state):
            time.sleep(1)
            view.show_msgbox("LEVEL COMPLETE!")


    def play(self, view, levels):
        for level in levels:
            self._play_level(view, level)
