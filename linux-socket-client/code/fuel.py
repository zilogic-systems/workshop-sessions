#!/usr/bin/env python3
"""
Fuel gauge that receives sensor data through UDP.
"""

import socket

import gi
gi.require_version('Gtk', '3.0')
from gi.repository import Gtk
from gi.repository import GObject


class FuelGauge:
    def __init__(self):
        self._sock = None
        self._fuel_levelbar = None
        self._fuel_label = None

    def on_main_window_destroy(self, *args):
        Gtk.main_quit()

    def poll_fuel_sensor(self):
        """Checks if notification available from fuel sensor."""

        GObject.timeout_add(1000, self.poll_fuel_sensor)

        try:
            cmd, _ = self._sock.recvfrom(4096)
        except socket.timeout:
            return

        if cmd[0] == ord('F'):
            try:
                level = int(cmd[1:])

                self._fuel_levelbar.set_value(level / 100.0)
                self._fuel_label.set_text(f"{level}%")

            except ValueError:
                pass

    def main(self):

        builder = Gtk.Builder()
        builder.add_from_file("fuel.glade")
        builder.connect_signals(self)

        window = builder.get_object("main_window")
        window.show_all()

        self._fuel_levelbar = builder.get_object("fuel_levelbar")
        self._fuel_label = builder.get_object("fuel_label")

        self._sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self._sock.bind(("localhost", 5000))
        self._sock.settimeout(0.01)

        GObject.timeout_add(1000, self.poll_fuel_sensor)

        Gtk.main()


if __name__ == "__main__":
    FuelGauge().main()
