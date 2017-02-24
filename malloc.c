/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsanzey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 11:49:14 by tsanzey           #+#    #+#             */
/*   Updated: 2017/02/24 12:14:56 by tsanzey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void		*ft_malloc(size_t size)
{
	void	*ptr;

	if (size <= 0)
		return (NULL);
	else if (size <= TINY_SIZE)
		ptr = allocate_tiny(size);
	else if (size <= SMALL_SIZE)
		ptr = allocate_small(size);
	else
		ptr = allocate_large(size + sizeof(t_header));
	if (ptr == MAP_FAILED)
		return (NULL);
	return (ptr);
}

void		*malloc(size_t size)
{
	void *ptr;

	pthread_mutex_lock(&g_mutex);
	ptr = ft_malloc(size);
	pthread_mutex_unlock(&g_mutex);
	return (ptr);
}
