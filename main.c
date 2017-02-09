#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int			main(void)
{
	char	*str;

	str = (char*)malloc(sizeof(char) * 10);
	printf("ptr %p\n", str);
	return (0);
}
