from unittest import TestCase
from mock import patch
from sokoban.view import PyGameGL

class ViewTestCase(TestCase):
    @patch("sokoban.view.pygame")
    def test_set_size(self, mpygame):
        gl = PyGameGL()
        gl.resize(20, 30)

        mpygame.display.set_mode.assert_called_with((20, 30))
