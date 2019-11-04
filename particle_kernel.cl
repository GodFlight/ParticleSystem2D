
#include "../include/particale_system.h"

__kernel void particle(__global int *img, __global t_particle *pt)
{
	int gid = get_global_id(0);
	size_t particl_number = gid % PARTICLE_COUNT;
	int color = 0xFF0000;

	img[(int)pt[particl_number].pos.x + (int)pt[particl_number].pos.y * WIDTH] = color;
}