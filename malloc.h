#ifndef MALLOC_H
# define MALLOC_H

// # define TINY_SIZE		(size_t)getpagesize() * 8
// # define SMALL_SIZE		(size_t)getpagesize() * 16
# define TINY_SIZE			(size_t)32
# define SMALL_SIZE			(size_t)64
// # define TINY_ZONE			(size_t)TINY_SIZE * 100
# define TINY_ZONE			(size_t)256
// # define SMALL_ZONE			(size_t)(SMALL_SIZE + sizeof(t_header)) * 100
# define SMALL_ZONE			(size_t)512

# define PROT			PROT_READ | PROT_WRITE
# define MAP			MAP_ANON | MAP_PRIVATE

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include "libft/libft.h"

typedef struct 		s_header
{
	void			*mem;
	size_t			size;
	int				free;
	struct s_header	*next;
}					t_header;

typedef struct 		s_env
{
	struct s_header	*tiny;
	struct s_header	*small;
	struct s_header	*large;
}					t_env;

t_env				g_env;

void				free(void *ptr);
void				*malloc(size_t size);
void				*realloc(void *ptr, size_t size);
void				show_alloc_mem(void);
void				show_list(void);

#endif
