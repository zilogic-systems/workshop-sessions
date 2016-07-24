from unittest import TestCase
from mock import patch
from mock import Mock

from sokoban.view import PyGameGL
from sokoban.utils import Key

### START: patch-mixin.py
class PatchMixin(object):
    """
    Testing utility mixin that provides methods to patch objects so
    that they will get unpatched automatically.
    """

    def patch(self, *args, **kwargs):
        patcher = patch(*args, **kwargs)
        self.addCleanup(patcher.stop)
        return patcher.start()
### END: patch-mixin.py

### START: read-key-undo.py
class ViewTestCase(PatchMixin, TestCase):
    def test_read_key_returns_undo_for_backspace(self):
        # Arrange
        mpygame = self.patch("sokoban.view.pygame")
        mevent = Mock(type=mpygame.KEYDOWN, key=mpygame.K_BACKSPACE)
        mpygame.event.wait.return_value = mevent
        # Act
        gl = PyGameGL()
        key = gl.read_key()
        # Assert
        self.assertEqual(key, Key.UNDO)
### END: read-key-undo.py

