#include <stdio.h>
#include "malloc.h"
#include <sys/mman.h>

void		*malloc(size_t size)
{
	void	*ptr;

	if (size <= 0)
		return (NULL);
	if ((ptr = mmap(0, size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0)) == MAP_FAILED)
		return (NULL);
	printf("my malloc\n");
	return (ptr);
}
