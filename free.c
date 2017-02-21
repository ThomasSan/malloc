#include "malloc.h"

// set free a 1
// parcourir la liste si celui la et le next sont free les fusionner.

void		free(void *ptr)
{
	t_header *tmp;

	tmp = (void*)ptr - 32;
	tmp->free = 1;
}