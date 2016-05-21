#define UART_TX_REG (*(unsigned int *)0x40100000)

int printf(char *str)
{
	int len = 0;

	while ((*(str + len)) != 0) {
		UART_TX_REG = *(str + len++);
	}
}

int main()
{
	printf("Hello World");
}
