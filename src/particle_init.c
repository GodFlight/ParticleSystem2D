#include "particale_system.h"

void	particle_init(t_particle **partcl)
{
	size_t i;

	i = (size_t)(-1);
	if (!(*partcl = (t_particle *)ft_memalloc(sizeof(t_particle ) * PARTICLE_COUNT)))
		exit (-1);
	while (++i < PARTICLE_COUNT)
	{
		(*partcl)[i].pos.x = rand() % WIDTH;
		(*partcl)[i].pos.y = rand() % HEIGHT;
		(*partcl)[i].velocity.y = 0.0f;
		(*partcl)[i].velocity.y = 0.0f;
	}
}
