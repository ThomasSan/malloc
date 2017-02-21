#include "malloc.h"
#include <sys/mman.h>

//chercher un morceau de memoire libre
// si il n'y en as pas ? mapper un nouveau morceau et ajouter un nouveau header a la fin.
// si il y a enregister et rajouter un header apres

//pour le premier bout ? mapper g_env.tiny;
//sinon le mapper apres le last element

/*
void		show_list(void)
{
	t_header *tmp;

	tmp = g_env.tiny;
	while (tmp->next)
	{
		printf("%p => %p\n", tmp, tmp->mem);
		printf("\tsize %zu\n", tmp->size);
		printf("\tfree %d\n", tmp->free);
		printf("\tnext %p\n", tmp->next);
		tmp = tmp->next;
	}
}
*/

void		fill_info(size_t size, t_header **add)
{
	t_header	*tmp;
	t_header	*tmp2;
	t_header	*next;

	tmp = *add;
	next = tmp->next ? tmp->next : NULL ;
	tmp->mem = tmp + 1;
	tmp->free = 0;
	tmp->next = (void*)tmp->mem + size;
	tmp2 = tmp->next;
	tmp2->mem = tmp2 + 1;
	tmp2->size = tmp->size - size - sizeof(t_header);
	tmp->size = size;
	tmp2->free = 1;
	tmp2->next = next;
}

void		fill_fit(size_t size, t_header **add)
{
	t_header	*tmp;

	tmp = *add;
	tmp->mem = tmp + 1;
	tmp->free = 0;
	tmp->size = size;
}

t_header		*get_last_header(t_header **list)
{
	t_header *tmp;

	tmp = *list;
	if (!tmp)
		return (NULL);
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

t_header		*map_tiny_chunk(size_t zone)
{
	t_header *last;

	if (!g_env.tiny)
	{
		// printf("MMAP\n");
		if ((g_env.tiny = (t_header*)mmap(0, zone, PROT, MAP, -1, 0)) == MAP_FAILED)
			return (NULL);
		return (g_env.tiny);
	}
	else
	{
		last = get_last_header(&(g_env.tiny));
		// printf("MMAP\n");
		if ((last->next = (t_header*)mmap(0, zone, PROT, MAP, -1, 0)) == MAP_FAILED)
			return (NULL);
		return (last->next);
	}
	return (NULL);
}

t_header		*map_small_chunk(size_t zone)
{
	t_header *last;

	if (!g_env.small)
	{
		// printf("MMAP\n");
		if ((g_env.small = (t_header*)mmap(0, zone, PROT, MAP, -1, 0)) == MAP_FAILED)
			return (NULL);
		return (g_env.small);
	}
	else
	{
		last = get_last_header(&(g_env.small));
		// printf("MMAP\n");
		if ((last->next = (t_header*)mmap(0, zone, PROT, MAP, -1, 0)) == MAP_FAILED)
			return (NULL);
		return (last->next);
	}
	return (NULL);
}

t_header		*find_free_chunk(t_header **list, size_t size)
{
	t_header *tmp;

	tmp = *list;
	while (tmp)
	{
		if (tmp->free && tmp->size >= (size + sizeof(t_header)))
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

t_header		*perfect_fit(t_header **list, size_t size)
{
	t_header *tmp;

	tmp = *list;
	while (tmp)
	{
		if (tmp->free && tmp->size == size && tmp->next)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

void		*allocate_tiny(size_t size)
{
	t_header	*ptr;

	// printf("TINY\n");
	if ((ptr = perfect_fit(&(g_env.tiny), size)))
	{
		fill_fit(size, &ptr);
		return (ptr->mem);
	}
	if (!(ptr = find_free_chunk(&(g_env.tiny), size))) // si c'est le premier tiny, ou qu'il n'y a plus de place.
	{
		ptr = map_tiny_chunk(TINY_ZONE);
		ptr->size = TINY_ZONE - sizeof(t_header);
		fill_info(size, &ptr);
		return (g_env.tiny->mem);
	}
	fill_info(size, &ptr);
	return (ptr->mem);
}

void		*allocate_small(size_t size)
{
	t_header	*ptr;

	// printf("SMALL\n");
	if ((ptr = perfect_fit(&(g_env.small), size)))
	{
		fill_fit(size, &ptr);
		return (ptr->mem);
	}
	if (!(ptr = find_free_chunk(&(g_env.small), size))) // si c'est le premier small, ou qu'il n'y a plus de place.
	{
		ptr = map_small_chunk(SMALL_ZONE);
		ptr->size = SMALL_ZONE - sizeof(t_header);
		fill_info(size, &ptr);
		return (g_env.small->mem);
	}
	fill_info(size, &ptr);
	return (ptr->mem);
}

// Mapper un nouveau bout de size + header
// Mettre un Header
// pointe sur Mem
// size
// free = 0

void		*allocate_large(size_t size)
{
	t_header	*ptr;

	if (!g_env.large) // si c'est le premier large
	{
		// printf("MMAP\n");
		if ((g_env.large = (t_header*)mmap(0, size + sizeof(t_header), PROT, MAP, -1, 0)) == MAP_FAILED)
			return (NULL);
		ptr = g_env.large;
	}
	else
	{
		ptr = get_last_header(&(g_env.large));
		// printf("MMAP\n");
		if ((ptr->next = (t_header*)mmap(0, size + sizeof(t_header), PROT, MAP, -1, 0)) == MAP_FAILED)
			return (NULL);
		ptr = ptr->next;
	}
	ptr->mem = ptr + 1;
	ptr->size = size;
	ptr->free = 0;
	return (ptr->mem);
}

void		*malloc(size_t size)
{
	void	*ptr;

	// printf("MALLOC\n");
	if (size <= 0)
		return (NULL);
	if (size <= TINY_SIZE)
		ptr = allocate_tiny(size);
	else if (size <= SMALL_SIZE)
		ptr = allocate_small(size);
	else
		ptr = allocate_large(size);
	if (ptr == MAP_FAILED)
		return (NULL);
	return (ptr);
}
