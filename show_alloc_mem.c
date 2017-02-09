#include "malloc.h"

void		show_alloc_mem(void)
{
	size_t		total;

	total = 0;
	if (g_env->tiny)
	{
		ft_putstr("TINY : ");
		// ft_putnbr(g_env->tiny); // afficher le debut de la zone memoire tiny
	}
	while (g_env->tiny)
	{
		ft_putstr();
		g_env->tiny = g_env->tiny->next;
	}
}
