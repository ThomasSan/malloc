#include "malloc.h"

void		iterate_mem(void *ptr)
{
	int 			i;
	unsigned char	*tmp;

	i = 0;
	tmp = (unsigned char *)ptr;
	while (i < 4)
	{
		printf("tmp + %d = %p\n", i, tmp + 32);
		i++;
	}
}

int			main(void)
{
	char		*str1;
	char		*str2;
	char		*str3;
	char		*str4;
	char		*str5;
	char		*str6;
	char		*str7;
	t_header	*head;

	printf("Tiny : %zu, Zone : %zu\n", TINY_SIZE, TINY_ZONE);
	str1 = malloc(42);
	str2 = malloc(32);
	str3 = malloc(10);
	str4 = malloc(32);
	str5 = malloc(10);
	str6 = malloc(32);
	str7 = malloc(64);
	show_alloc_mem();
	return (0);
}
