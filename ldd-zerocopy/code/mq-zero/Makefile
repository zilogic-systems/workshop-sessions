all: player viewer

clean:
	rm -f player viewer

player: player.c
	gcc log.c player.c -o player $$(sdl-config --cflags --libs) -lrt

viewer: viewer.c
	gcc log.c viewer.c -o viewer $$(sdl-config --cflags --libs) -lrt
