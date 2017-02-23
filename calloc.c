/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsanzey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 19:57:35 by tsanzey           #+#    #+#             */
/*   Updated: 2017/02/23 20:06:59 by tsanzey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void		*calloc(size_t count, size_t size)
{
	void	*ptr;

	ft_putstr("Calloc\n");
	ptr = malloc(count * size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, count*size);	
	ft_putstr("Bite\n");
	return (ptr);
}

void		*reallocf(void *ptr, size_t size)
{
	void	*ret;

	ft_putstr("Reallocf\n");
	ret = realloc(ptr, size);
	if (!ret)
	{
		free(ptr);
		return (NULL);
	}
	ft_putstr("Bite\n");
	return (ret);
}
