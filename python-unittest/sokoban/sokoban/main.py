from .view import PyGameGL
from .view import GameView
from .controller import GameController

def _read_levels():
    levels = []
    curr_level = []
    for line in open("levels.txt"):
        try:
            if line[0] == ";":
                levels.append(curr_level)
                curr_level = []
            else:
                curr_level.append(line)
        except IndexError:
            pass

    return levels


def main():
    gl = PyGameGL()
    view = GameView(gl)
    levels = _read_levels()
    ctl = GameController()
    ctl.play(view, levels)


if __name__ == "__main__":
    main()
