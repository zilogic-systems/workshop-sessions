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
	struct mq_attr attr;

	memset(&attr, 0, sizeof(attr));
	attr.mq_msgsize = MAX_WIDTH * MAX_HEIGHT * BPP;
	attr.mq_maxmsg = 1;

	mqd = mq_open("/video", O_RDWR | O_CREAT, 0666, &attr);
	if (mqd == -1) {
		log_error("error opening message queue: %s", strerror(errno));
		exit(1);
	}
	
	ret = SDL_Init(SDL_INIT_VIDEO);
	if (ret == -1) {
		log_error("initializing SDL failed: %s", SDL_GetError());
		exit(1);
	}

	window = SDL_SetVideoMode(MAX_WIDTH, MAX_HEIGHT,
				  32,
				  SDL_SWSURFACE);
	if (window == NULL) {
		log_error("setting video mode failed: %s", SDL_GetError());
		SDL_Quit();
		exit(1);
	}

	while (1) {
		SDL_Surface *frame;
		SDL_Rect window_rect;
		Uint32 rmask, gmask, bmask, amask;
		char pixels[MAX_WIDTH * MAX_HEIGHT * BPP];

		ret = mq_receive(mqd, pixels, sizeof(pixels), NULL);
		if (ret == -1) {
			log_error("reading mq failed: %s", strerror(errno));
			break;
		}

		rmask = 0xff0000;
		gmask = 0xff00;
		bmask = 0xff;
		amask = 0x00;

		frame = SDL_CreateRGBSurfaceFrom(pixels, MAX_WIDTH, MAX_HEIGHT, BPP * 8,
						 MAX_WIDTH * BPP, rmask, gmask, bmask, amask);
		if (frame == NULL) {
			log_error("loading bitmap failed: %s", SDL_GetError());
			break;
		}
		
		window_rect.x = 0;
		window_rect.y = 0;
		window_rect.w = MAX_WIDTH;
		window_rect.h = MAX_HEIGHT;

		ret = SDL_BlitSurface(frame,
				      NULL,
				      window,
				      &window_rect);
		assert(ret != -1);
		SDL_FreeSurface(frame);

		SDL_UpdateRect(window, 0, 0, 0, 0);
	}


	SDL_FreeSurface(window);
	SDL_Quit();
}
