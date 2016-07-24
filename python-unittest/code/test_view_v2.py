from unittest import TestCase
from mock import patch
from mock import Mock

from sokoban.view import PyGameGL
from sokoban.utils import Key


class ViewTestCase(TestCase):
    @patch("sokoban.view.pygame")
    def test_set_size(self, mpygame):
        gl = PyGameGL()
        gl.resize(20, 30)

        mpygame.display.set_mode.assert_called_with((20, 30))

    @patch("sokoban.view.pygame")
    def test_read_key_returns_quit_for_quit_event(self, mpygame):
        mevent = Mock(type=mpygame.QUIT)
        mpygame.event.wait.return_value = mevent

        gl = PyGameGL()
        key = gl.read_key()

        self.assertEqual(key, Key.QUIT)

    ### START: read-key-undo.py
    @patch("sokoban.view.pygame")
    def test_read_key_returns_undo_for_backspace(self, mpygame):
        # Arrange
        mevent = Mock(type=mpygame.KEYDOWN, key=mpygame.K_BACKSPACE)
        mpygame.event.wait.return_value = mevent

        # Act
        gl = PyGameGL()        
        key = gl.read_key()

        # Assert
        self.assertEqual(key, Key.UNDO)
    ### END: read-key-undo.py

    ### START: read-key-undo-with.py
    def test_read_key_returns_undo_for_backspace_cm(self):
        # Arrange
        mpygame = Mock()
        mevent = Mock(type=mpygame.KEYDOWN, key=mpygame.K_BACKSPACE)
        mpygame.event.wait.return_value = mevent

        # Act
        with patch("sokoban.view.pygame", mpygame):
            gl = PyGameGL()
            key = gl.read_key()

        # Assert
        self.assertEqual(key, Key.UNDO)
    ### END: read-key-undo-with.py

