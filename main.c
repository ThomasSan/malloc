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
	char		*str8;
	t_header	*head;

	printf("Tiny : %zu, Zone : %zu\n", TINY_SIZE, TINY_ZONE);
	str1 = malloc(42);
	ft_memset(str1, '#', 42);
	str2 = malloc(84);
	str3 = malloc(3725);
	str8 = malloc(48847);
	printf("<----------------Before Free------------->\n");
	show_alloc_mem();
	printf("<----------------After Free------------->\n");
	free(str1);
	show_alloc_mem();
	printf("<----------------After Alloc------------->\n");
	str1 = malloc(42);
	show_alloc_mem();
	printf("<----------------Realloc------------->\n");
	str1 = realloc(str1, 2000);
	show_alloc_mem();
	// 	int	i = 0;
	// 	char	*str;
	// 	while (i < 102)
	// 	{
	// 		str = malloc(1024);
	// 		str[0] = 42;
	// //		free(str);
	// 		i++;
	// 	}
	// show_alloc_mem();
	return (0);
}
