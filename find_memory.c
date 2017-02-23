/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsanzey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 11:47:27 by tsanzey           #+#    #+#             */
/*   Updated: 2017/02/23 13:59:57 by tsanzey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_header	*find_ptr(void *ptr, t_header *list, int flag)
{
	t_header *ret;
	t_header *prev;

	ret = NULL;
	prev = NULL;
	while (list)
	{
		if (flag && prev && ptr >= prev->mem && list->mem > ptr)
			return (prev->mem);
		if (ptr == list->mem)
			return (list->mem);
		prev = list;
		list = list->next;
	}
	return (ret);
}

t_header	*find_mem_chunk(void *ptr, int flag)
{
	t_header *ret;

	if ((ret = find_ptr(ptr, g_env.tiny, flag)))
		return (ret - 1);
	if ((ret = find_ptr(ptr, g_env.small, flag)))
		return (ret - 1);
	if ((ret = find_ptr(ptr, g_env.large, flag)))
		return (ret - 1);
	return (NULL);
}

t_header	*get_last_header(t_header **list)
{
	t_header *tmp;

	tmp = *list;
	if (!tmp)
		return (NULL);
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

t_header	*find_free_chunk(t_header **list, size_t size)
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
