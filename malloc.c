#include <stdio.h>
#include "malloc.h"
#include <sys/mman.h>

//chercher un morceau de memoire libre
// si il n'y en as pas ? mapper un nouveau morceau et ajouter un nouveau header a la fin.
// si il y a enregister et rajouter un header apres


void		fill_info(size_t size, size_t fmt, t_header **add)
{
	t_header	*tmp;
	t_header	*tmp2;

	tmp = *add;
	tmp->mem = tmp + 1;
	tmp->size = size;
	tmp->free = 0;
	tmp->next = (void*)tmp->mem + tmp->size;
	tmp2 = tmp->next;
	tmp2->mem = tmp2 + 1;
	tmp2->size = fmt - size - (sizeof(t_header) * 2);
	tmp2->free = 1;
	tmp2->next = NULL;
}

void		*map_new_chunk()
{
	if ((g_env.tiny = (t_header*)mmap(0, TINY_SIZE, PROT, MAP, -1, 0)) == MAP_FAILED)
		return (NULL);

}

void		*find_free_chunk(t_header **list, size_t size)
{
	t_header *tmp;

	tmp = *list;
	while (tmp)
	{
		if (tmp->free && tmp->size >= size)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

void		*allocate_tiny(size_t size)
{
	if (!g_env.tiny) // si c'est le premier tiny
	{
		fill_info(size, TINY_SIZE, &(g_env.tiny));
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
		ptr = allocate_tiny(size);
	else if (size <= SMALL_SIZE)
		ptr = allocate_tiny(size);
	else
		ptr = allocate_tiny(size);
	if (ptr == MAP_FAILED)
		return (NULL);
	return (ptr);
}
