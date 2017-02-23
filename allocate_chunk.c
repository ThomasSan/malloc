/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocate_chunk.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsanzey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 12:10:20 by tsanzey           #+#    #+#             */
/*   Updated: 2017/02/23 12:27:24 by tsanzey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_header			*map_tiny_chunk(size_t zone)
{
	t_header	*last;

	if (!g_env.tiny)
	{
		if ((g_env.tiny = (t_header*)mmap(0, zone, PROT, MAP, -1, 0))
			== MAP_FAILED)
			return (NULL);
		return (g_env.tiny);
	}
	else
	{
		last = get_last_header(&(g_env.tiny));
		if ((last->next = (t_header*)mmap(0, zone, PROT, MAP, -1, 0))
			== MAP_FAILED)
			return (NULL);
		return (last->next);
	}
	return (NULL);
}

t_header			*map_small_chunk(size_t zone)
{
	t_header	*last;

	if (!g_env.small)
	{
		if ((g_env.small = (t_header*)mmap(0, zone, PROT, MAP, -1, 0))
			== MAP_FAILED)
			return (NULL);
		return (g_env.small);
	}
	else
	{
		last = get_last_header(&(g_env.small));
		if ((last->next = (t_header*)mmap(0, zone, PROT, MAP, -1, 0))
			== MAP_FAILED)
			return (NULL);
		return (last->next);
	}
	return (NULL);
}

void			*allocate_tiny(size_t size)
{
	t_header	*ptr;

	if ((ptr = perfect_fit(&(g_env.tiny), size)))
	{
		fill_fit(size, &ptr);
		return (ptr->mem);
	}
	if (!(ptr = find_free_chunk(&(g_env.tiny), size + sizeof(t_header))))
	{
		ptr = map_tiny_chunk(TINY_ZONE);
		ptr->size = TINY_ZONE - sizeof(t_header);
		fill_info(size, &ptr);
		return (g_env.tiny->mem);
	}
	fill_info(size, &ptr);
	return (ptr->mem);
}

void			*allocate_small(size_t size)
{
	t_header	*ptr;

	if ((ptr = perfect_fit(&(g_env.small), size)))
	{
		fill_fit(size, &ptr);
		return (ptr->mem);
	}
	if (!(ptr = find_free_chunk(&(g_env.small), size + sizeof(t_header))))
	{
		ptr = map_small_chunk(SMALL_ZONE);
		ptr->size = SMALL_ZONE - sizeof(t_header);
		fill_info(size, &ptr);
		return (g_env.small->mem);
	}
	fill_info(size, &ptr);
	return (ptr->mem);
}

void			*allocate_large(size_t size)
{
	t_header	*ptr;

	if (!(ptr = find_free_chunk(&(g_env.large), size)))
	{
		ptr = get_last_header(&(g_env.large));
		if (ptr)
		{
			if ((ptr->next = (t_header*)mmap(0, size, PROT, MAP, -1, 0))
				== MAP_FAILED)
				return (NULL);
			ptr = ptr->next;
		}
		else
		{
			if ((g_env.large = (t_header*)mmap(0, size, PROT, MAP, -1, 0))
				== MAP_FAILED)
				return (NULL);
			ptr = g_env.large;
		}
	}
	ptr->mem = ptr + 1;
	ptr->size = size;
	ptr->free = 0;
	ptr->next = NULL;
	return (ptr->mem);
}
