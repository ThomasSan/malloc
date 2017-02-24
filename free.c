/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsanzey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 11:48:24 by tsanzey           #+#    #+#             */
/*   Updated: 2017/02/24 12:14:02 by tsanzey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void		free_other(t_header *list, t_header *ptr, size_t size, size_t tmp)
{
	t_header	*prev;
	size_t		total;

	prev = NULL;
	total = 0;
	while (list)
	{
		tmp = sizeof(t_header) + list->size;
		total += tmp;
		if (prev && prev == ptr && list->free && total <= size)
		{
			prev->size += list->size + sizeof(t_header);
			prev->next = list->next;
		}
		else if (prev && list == ptr && prev->free && total <= size)
		{
			prev->size += list->size + sizeof(t_header);
			prev->next = list->next;
		}
		else
			prev = list;
		if (total > size)
			total = tmp;
		list = list->next;
	}
}

void		free_large(t_header *ptr)
{
	t_header	*prev;
	t_header	*list;

	list = g_env.large;
	prev = NULL;
	while (list)
	{
		if (list == ptr)
		{
			if (prev)
				prev->next = list->next;
			munmap(ptr, ptr->size + sizeof(t_header));
			return ;
		}
		prev = list;
		list = list->next;
	}
}

void		join_headers(t_header *ptr)
{
	t_header	*list;
	size_t		page;

	list = find_list(ptr);
	page = 0;
	if (!list)
		return ;
	if (ptr->size <= TINY_SIZE)
		page = TINY_SIZE;
	else if (ptr->size <= SMALL_SIZE)
		page = SMALL_SIZE;
	if (!page)
		free_large(ptr);
	else
		free_other(list, ptr, page, 0);
}

void		free(void *ptr)
{
	t_header *tmp;

	if (!ptr)
		return ;
	tmp = find_mem_chunk(ptr, 1);
	if (!tmp)
		return ;
	pthread_mutex_lock(&g_mutex);
	tmp->free = 1;
	join_headers(tmp);
	pthread_mutex_unlock(&g_mutex);
}
