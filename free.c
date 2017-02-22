#include "malloc.h"

// set free a 1
// parcourir la liste si celui la et le next sont free les fusionner.

void		free(void *ptr)
{
	t_header *tmp;

	// ft_putstr("FREE - ");
	// put_hexa((unsigned long)ptr);
	// ft_putchar('\n');
	if (!ptr)
		return ;
	tmp = find_mem_chunk(ptr);
	if (!tmp)
		return ;
	tmp->free = 1;
}