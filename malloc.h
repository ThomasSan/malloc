#ifndef MALLOC_H
# define MALLOC_H

# define TINY_SIZE		getpagesize() * 8;
# define SMALL_SIZE		getpagesize() * 16;
# define TINY			TINY_SIZE * 100;
# define SMALL			SMALL_SIZE * 100;

# include <stdlib.h>
# include "libft.h"

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
#endif
