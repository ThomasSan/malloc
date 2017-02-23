/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsanzey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 11:49:55 by tsanzey           #+#    #+#             */
/*   Updated: 2017/02/23 13:12:52 by tsanzey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void		put_hexa(unsigned long h)
{
	const char *hex = "0123456789abcdef";

	if (h >= 16)
	{
		put_hexa(h / 16);
		put_hexa(h % 16);
	}
	else
		ft_putchar(hex[h]);
}

void		put_pointer(void *ptr)
{
	ft_putstr("0x");
	put_hexa((unsigned long)ptr);
}

size_t		print_memory(char *str, t_header *list)
{
	size_t		total;

	total = 0;
	if (list)
	{
		ft_putstr(str);
		put_pointer(list);
		ft_putchar('\n');
	}
	while (list)
	{
		if (list->free == 0)
		{
			put_pointer(list->mem);
			ft_putstr(" - ");
			put_pointer((void*)list->mem + list->size);
			ft_putstr(" : ");
			print_num(list->size);
			ft_putendl(" octets");
			total += list->size;
		}
		list = list->next;
	}
	return (total);
}

void		show_alloc_mem(void)
{
	size_t		total;

	total = 0;
	total += print_memory("TINY : ", g_env.tiny);
	total += print_memory("SMALL : ", g_env.small);
	total += print_memory("LARGE : ", g_env.large);
	printf("total : %zu octets\n", total);
}
