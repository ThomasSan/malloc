/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsanzey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 11:48:24 by tsanzey           #+#    #+#             */
/*   Updated: 2017/02/23 20:08:31 by tsanzey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

/*
** ft_putstr("FREE - ");
** put_hexa((unsigned long)ptr);
** ft_putchar('\n');
*/

void		free_tiny_small(t_header *list, t_header *ptr, size_t size)
{
	t_header	*prev;
	size_t		total;
	size_t		tmp;

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
			ft_putstr("Here\n");
			prev->size += list->size + sizeof(t_header);
			prev->next = list->next;
			ft_putstr("BITE\n");
		}
		else
			prev = list;
		if (total > size)
			total = tmp;
		ft_putstr("TTT\n");
		list = list->next;
	}
}

void			free_large(t_header *ptr)
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

void			join_headers(t_header *ptr)
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
		free_tiny_small(list, ptr, page);
}

void		free(void *ptr)
{
	t_header *tmp;

	ft_putstr("Free\n");
	if (!ptr)
		return ;
	tmp = find_mem_chunk(ptr, 1);
	if (!tmp)
		return ;
	tmp->free = 1;
	join_headers(tmp);
}
