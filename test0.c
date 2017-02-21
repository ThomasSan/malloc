#include <sys/mman.h>
#include <unistd.h>
#include <stdlib.h>

int		main(void)
{
	int i;
	char *addr;

	i = 0;
	//addr = (char*)mmap(0, getpagesize(), PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	//addr[0] = 42;
	while (i < 100)
	{
		//addr = (char*)malloc(1024);
		//addr = (char*)mmap(0, 1, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
		//addr[0] = 42;
		i++;
	}
	return (0);
}
