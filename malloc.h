/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsanzey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 13:58:05 by tsanzey           #+#    #+#             */
/*   Updated: 2017/02/23 20:05:02 by tsanzey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# define TINY_SIZE			(size_t)getpagesize() * 2
# define SMALL_SIZE			(size_t)getpagesize() * 16
# define TINY_ZONE			(size_t)(TINY_SIZE + sizeof(t_header)) * 100
# define SMALL_ZONE			(size_t)(SMALL_SIZE + sizeof(t_header)) * 100

# define PROT			PROT_READ | PROT_WRITE
# define MAP			MAP_ANON | MAP_PRIVATE

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/mman.h>
# include "libft/libft.h"
# include <pthread.h>

typedef enum		e_type
{
	TINY,
	SMALL,
	LARGE
}					t_type;

typedef struct		s_header
{
	void			*mem;
	size_t			size;
	int				free;
	struct s_header	*next;
}					t_header;

typedef struct		s_env
{
	struct s_header	*tiny;
	struct s_header	*small;
	struct s_header	*large;
}					t_env;

t_env				g_env;
pthread_mutex_t		g_mutex;

void				free(void *ptr);
void				*malloc(size_t size);
void				*calloc(size_t count, size_t size);
void				*realloc(void *ptr, size_t size);
void				*reallocf(void *ptr, size_t size);
void				show_alloc_mem(void);

t_header			*find_mem_chunk(void *ptr, int flag);
t_header			*get_last_header(t_header **list);
t_header			*find_free_chunk(t_header **list, size_t size);

void				fill_info(size_t size, t_header **add);
void				fill_fit(size_t size, t_header **add);
t_header			*perfect_fit(t_header **list, size_t size);

void				*allocate_tiny(size_t size);
void				*allocate_small(size_t size);
void				*allocate_large(size_t size);
t_header			*find_list(t_header *ptr);

void				print_num(unsigned int n);
void				put_hexa(unsigned long h);

#endif
