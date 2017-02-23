/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsanzey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 11:48:24 by tsanzey           #+#    #+#             */
/*   Updated: 2017/02/23 11:48:52 by tsanzey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

// parcourir la liste si celui la et le next sont free les fusionner.

void		free(void *ptr)
{
	t_header *tmp;

	// ft_putstr("FREE - ");
	// put_hexa((unsigned long)ptr);
	// ft_putchar('\n');
	if (!ptr)
		return ;
	tmp = find_mem_chunk(ptr, 1);
	if (!tmp)
		return ;
	tmp->free = 1;
}
