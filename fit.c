/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsanzey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 11:59:04 by tsanzey           #+#    #+#             */
/*   Updated: 2017/02/23 13:57:11 by tsanzey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void		fill_info(size_t size, t_header **add)
{
	t_header	*tmp;
	t_header	*tmp2;
	t_header	*next;

	tmp = *add;
	next = tmp->next ? tmp->next : NULL;
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

t_header	*perfect_fit(t_header **list, size_t size)
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
