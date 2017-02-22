#include "malloc.h"

t_header	*find_ptr(void *ptr, t_header *list)
{
	t_header *ret;
	t_header *prev;

	ret = NULL;
	prev = NULL;
	while (list)
	{
		if ((prev && ptr >= prev->mem && list->mem > ptr))
			return (prev->mem);
		if (ptr == list->mem)
			return (list->mem);
		prev = list;
		list = list->next;
	}
	return (ret);
}

t_header	*find_realloc_ptr(void *ptr, t_header *list)
{
	t_header *ret;
	t_header *prev;

	ret = NULL;
	prev = NULL;
	while (list)
	{
		if (ptr == list->mem)
			return (list->mem);
		prev = list;
		list = list->next;
	}
	return (ret);
}

t_header	*find_mem_chunk(void *ptr)
{
	t_header *ret;

	if ((ret = find_ptr(ptr, g_env.tiny)))
		return (ret - 1);
	if ((ret = find_ptr(ptr, g_env.small)))
		return (ret - 1);
	if ((ret = find_ptr(ptr, g_env.large)))
		return (ret - 1);
	return (NULL);
}

t_header	*realloc_chunk(void *ptr)
{
	t_header *ret;

	if ((ret = find_realloc_ptr(ptr, g_env.tiny)))
		return (ret - 1);
	if ((ret = find_realloc_ptr(ptr, g_env.small)))
		return (ret - 1);
	if ((ret = find_realloc_ptr(ptr, g_env.large)))
		return (ret - 1);
	return (NULL);
}
