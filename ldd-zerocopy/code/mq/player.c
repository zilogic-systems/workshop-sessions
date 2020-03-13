#include "log.h"

#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <sys/types.h>
#include <mqueue.h>

#include <string.h>
#include <assert.h>
#include <errno.h>

#include <SDL.h>

#define MAX_FRAMES 44
#define MAX_WIDTH  400
#define MAX_HEIGHT 400
#define BPP 4

int main()
{
	int i;
	int ret;
	SDL_Surface *window;
	mqd_t mqd;

	mqd = mq_open("/video", O_WRONLY);
	if (mqd == -1) {
		log_error("error opening message queue: %s", strerror(errno));
		exit(1);
	}
	
	ret = SDL_Init(SDL_INIT_VIDEO);
	if (ret == -1) {
		log_error("initializing SDL failed: %s", SDL_GetError());
		exit(1);
	}

	while (1) {
		for (i = 0; i < MAX_FRAMES; i++) {
			SDL_Surface *bmpframe;
			SDL_Surface *frame;
			SDL_Rect window_rect;
			char filename[32];

			snprintf(filename, sizeof(filename), "image-seq/frame-%02d.bmp", i);
			bmpframe = SDL_LoadBMP(filename);
			if (bmpframe == NULL) {
				log_error("loading bitmap failed: %s", SDL_GetError());
				break;
			}

			frame = bmpframe;
			SDL_LockSurface(frame);
			ret = mq_send(mqd, frame->pixels, MAX_WIDTH * MAX_HEIGHT * BPP, 0);
			if (ret == -1) {
				log_error("sending frame failed: %s", strerror(errno));
				break;
			}

			SDL_UnlockSurface(frame);			
			SDL_FreeSurface(frame);
			
			ret = usleep(100000);
			if (ret == -1)
				break;
		}

		if (i != MAX_FRAMES)
			break;
	}

	SDL_Quit();
}
