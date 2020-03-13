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
	mqd_t mqd_in;
	mqd_t mqd_out;
	int shmd;
	void *mem;
	int pos = 0; 

	mqd_in = mq_open("/video-in", O_WRONLY);
	if (mqd_in == -1) {
		log_error("error opening message queue: %s", strerror(errno));
		exit(1);
	}

	mqd_out = mq_open("/video-out", O_RDONLY);
	if (mqd_out == -1) {
		log_error("error opening message queue: %s", strerror(errno));
		exit(1);
	}

	shmd = shm_open("/video-mem", O_RDWR, 0);
	if (shmd == -1) {
		log_error("error opening shared memory: %s", strerror(errno));
		exit(1);
	}

	mem = mmap(NULL, IMGSIZE * MAX_BUFS, PROT_WRITE, MAP_SHARED, shmd, 0);
	if (mem == MAP_FAILED) {
		log_error("error mapping shared memory: %s", strerror(errno));
		exit(1);
	}

	for (i = 0; i < MAX_BUFS; i++) {
		ret = mq_send(mqd_in, (char *) &i, sizeof(i), 0);
		if (ret == -1) {
			log_error("error sending in mqd_in: %s", strerror(errno));
			exit(1);
		}
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
			char *buffer = mem;

			ret = mq_receive(mqd_out, (char *) &pos, sizeof(pos), NULL);
			if (ret == -1) {
				log_error("error receiving mqd_out: %s", strerror(errno));
				exit(1);
			}

			snprintf(filename, sizeof(filename), "image-seq/frame-%02d.bmp", i);
			bmpframe = SDL_LoadBMP(filename);
			if (bmpframe == NULL) {
				log_error("loading bitmap failed: %s", SDL_GetError());
				break;
			}

			frame = bmpframe;
			SDL_LockSurface(frame);
			memcpy(buffer + (IMGSIZE * pos), frame->pixels, IMGSIZE);
			
			ret = mq_send(mqd_in, (char *) &pos, sizeof(pos), 0);
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
