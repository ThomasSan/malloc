#include "malloc.h"

// size_t			print_memory(char *str, t_header list)
// {
// 	size_t total;

// 	total = 0;
// 	if (list)
// 	{
// 		ft_putstr(str);
// 		// ft_putnbr(g_env->tiny); // afficher le debut de la zone memoire tiny
// 	}
// 	while (list)
// 	{
// 		ft_putstr(g_env);
// 		g_env->tiny = g_env->tiny->next;
// 	}
// }

void		show_alloc_mem(void)
{
	size_t		total;

	total = 0;
	if (g_env.tiny)
	{
		ft_putstr("TINY : ");
		// ft_putnbr(g_env.tiny); // afficher le debut de la zone memoire tiny
	}
	while (g_env.tiny)
	{
		// ft_putstr(g_env);
		g_env.tiny = g_env.tiny->next;
	}
}
