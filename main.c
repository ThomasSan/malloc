#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
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
	char		*str;
	t_header	*head;

	str = (char*)malloc(sizeof(char) * 10);
	// head = (t_header*)malloc(sizeof(t_header));
	// head->size = 42;
	// head->free = 0;
	printf("str %p\n", str);
	printf("<----------------------------->\n");
	// iterate_mem(head);
	// printf("mem %p\n", head->mem);
	// printf("size %p\n", &head->size);
	// printf("free %p\n", &head->free);
	// printf("header %p\n", g_env);
	// printf("tiny %p\n", g_env.tiny);
	// show_alloc_mem();
	return (0);
}

// TINY : 0xA0000
// 0xA0020 - 0xA004A : 42 octets
// 0xA006A - 0xA00BE : 84 octets
// SMALL : 0xAD000
// 0xAD020 - 0xADEAD : 3725 octets
// LARGE : 0xB0000
// 0xB0020 - 0xBBEEF : 48847 octets
// Total : 52698 octets