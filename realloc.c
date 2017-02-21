#include "malloc.h"

// 1er cas : il y a la place tout de suite apres 
// !! Attention que la zone soit bien allouee a mem + size de mem;
// Sinon c'est deux zones differentes.
// A) Changer la size dans le header
// B) Remettre un Header apres la zone.
// C) Sauver le next de la zone. pour update le header
//

// xxxx oooo oooo xxxx ---- ---- ---- ---- xxxx
// 0   |    |    |96  |    |    add
// 64  |    |    |128 |    |	size
// 32  |    |    |128 |    |	mem
// 96  |    |    |256 |    |	next

// xxxx oooo oooo oooo xxxx ---- ---- ---- xxxx
// 32  |    |    |    |128 |    add
// 96  |    |    |    |96  |	size
// 32  |    |    |    |160 |	mem
// 128 |    |    |    |256 |	next


// 2e cas il n'ya pas de place tout de suite apres :
// set le free a 1,
// sauver le ptr de la zone memoire
// trouver un nouvel espace & le malloc
// puis memcpy

void				*realloc(void *ptr, size_t size)
{
	t_header	*tmp;
	void		*ret;

	tmp = (void*)ptr - 32;
	tmp->free = 1;
	if (!(ret = malloc(size)))
		return (NULL);
	ret = ft_memcpy(ret, tmp->mem, tmp->size);
	return (ret);
}