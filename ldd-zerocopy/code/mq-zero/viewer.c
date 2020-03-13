#include "log.h"

#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <sys/types.h>
#include <sys/mman.h>
#include <mqueue.h>

#include <string.h>
#include <assert.h>
#include <errno.h>

#include <SDL.h>

#define MAX_FRAMES 44
#define MAX_WIDTH  400
#define MAX_HEIGHT 400
#define BPP 4
#define IMGSIZE ((MAX_WIDTH) * (MAX_HEIGHT) * (BPP))
#define MAX_BUFS 4

int main()
{
	int i;
	int ret;
	SDL_Surface *window;
	struct mq_attr attr;
	mqd_t mqd_in;
	mqd_t mqd_out;
	int shmd;
	void *mem;

	memset(&attr, 0, sizeof(attr));
	attr.mq_msgsize = sizeof(int);
	attr.mq_maxmsg = MAX_BUFS;

	ret = mq_unlink("/video-in");
	if (ret == -1 && errno != ENOENT) {
		log_error("error removing message queue: %s", strerror(errno));
		exit(1);
	}
	
	mqd_in = mq_open("/video-in", O_RDWR | O_CREAT, 0666, &attr);
	if (mqd_in == -1) {
		log_error("error opening message queue: %s", strerror(errno));
		exit(1);
	}
	
	ret = mq_unlink("/video-out");
	if (ret == -1 && errno != ENOENT) {
		log_error("error removing message queue: %s", strerror(errno));
		exit(1);
	}

	mqd_out = mq_open("/video-out", O_RDWR | O_CREAT, 0666, &attr);
	if (mqd_out == -1) {
		log_error("error opening message queue: %s", strerror(errno));
		exit(1);
	}

	shmd = shm_open("/video-mem", O_RDWR | O_CREAT, 0666);
	if (shmd == -1) {
		log_error("error opening shared memory: %s", strerror(errno));
		exit(1);
	}

	ret = ftruncate(shmd, MAX_HEIGHT * MAX_HEIGHT * BPP * MAX_BUFS);
	if (ret == -1) {
		log_error("error truncating file: %s", strerror(errno));
		exit(1);
	}

	mem = mmap(NULL, IMGSIZE * MAX_BUFS, PROT_READ | PROT_WRITE,
		   MAP_SHARED, shmd, 0);
	if (mem == MAP_FAILED) {
		log_error("error mapping shared memory: %s", strerror(errno));
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
		char *pixels = mem;
		int pos;

		ret = mq_receive(mqd_in, (char *) &pos, sizeof(pos), NULL);
		if (ret == -1) {
			log_error("reading mq failed: %s", strerror(errno));
			break;
		}

		rmask = 0xff0000;
		gmask = 0xff00;
		bmask = 0xff;
		amask = 0x00;

		frame = SDL_CreateRGBSurfaceFrom(pixels + (IMGSIZE * pos),
						 MAX_WIDTH, MAX_HEIGHT, BPP * 8,
						 MAX_WIDTH * BPP,
						 rmask, gmask, bmask, amask);
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

		ret = mq_send(mqd_out, (char *) &pos, sizeof(pos), 0);
		if (ret == -1) {
			log_error("sending frame failed: %s", strerror(errno));
			break;
		}

		SDL_UpdateRect(window, 0, 0, 0, 0);
	}


	SDL_FreeSurface(window);
	SDL_Quit();
}
