#define LOG_BUF_BASE 0xA0010000
#define LOG_BUF_SIZE 0x100 

unsigned char * log_buffer = (unsigned char *) LOG_BUF_BASE;
int log_off = 0;

int printf(char *str)
{
	int len = 0;

	while ((*(str + len)) != 0) {
		*(log_buffer + log_off++) = *(str + len++);

		if (log_off == (LOG_BUF_BASE + LOG_BUF_SIZE))
			log_off = 0;
	}
}

int main()
{
	printf("Hello World");
	printf("Good Bye");
}
