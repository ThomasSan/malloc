#include <stdio.h>
#include <stdlib.h>

int		main(void)
{
	int i;
	char *addr;

	i = 0;
	while (i < 100)
	{
		addr = (char*)malloc(1024);
		addr[0] = 42;
		free(addr);
		i++;
	}
	return (0);
}
