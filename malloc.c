#include <stdio.h>
#include "malloc.h"
#include <sys/mman.h>

//chercher un morceau de memoire libre
// si il n'y en as pas ? mapper un nouveau morceau
// si il y a enregister et rajouter un header apres



void		*allocate_tiny(size_t size)
{
	// void	*tmp;
	if (!g_env.tiny) // si c'est le premier tiny
	{
		if ((g_env.tiny = (t_header*)mmap(0, TINY_SIZE, PROT, MAP, -1, 0)) == MAP_FAILED)
			return (NULL);
		g_env.tiny->mem = g_env.tiny + 1;
		g_env.tiny->size = size;
		g_env.tiny->free = 0;
		g_env.tiny->next = (void*)g_env.tiny->mem + g_env.tiny->size;
		printf("%p, %p, %p\n", g_env.tiny, g_env.tiny->mem, g_env.tiny->next);
		return (g_env.tiny->mem);
	}
	return (g_env.tiny->mem);
}

void		*malloc(size_t size)
{
	void	*ptr;

	if (size <= 0)
		return (NULL);
	if (size <= TINY_SIZE)
	{
		ptr = allocate_tiny(size);
	}
	else if (size <= SMALL_SIZE)
	{
		ptr = allocate_tiny(size);
	}
	else
	{
		ptr = allocate_tiny(size);
	}
	// if ((ptr = mmap(0, size, PROT, MAP, -1, 0)) == MAP_FAILED)
	// 	return (NULL);
	if (ptr == MAP_FAILED)
		return (NULL);
	return (ptr);
}
