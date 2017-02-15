#include "malloc.h"

size_t			print_memory(char *str, t_header *list)
{
	size_t total;

	total = 0;
	if (list)
	{
		ft_putstr(str);
		printf("%p\n", list); // afficher le debut de la zone memoire tiny
	}
	while (list)
	{
		if (list->free == 0)
			{
				printf("%p|| %p - %p : %zu octets\n", list, list->mem, (void*)list->mem + list->size, list->size);
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
