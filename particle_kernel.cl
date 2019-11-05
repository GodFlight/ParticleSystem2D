
#include "../include/particale_system.h"

__kernel void particle(__global int *img, __global t_particle *pt,
			__global t_mouse_events *mouse, float rand_x, float rand_y)
{
	int gid = get_global_id(0);
	size_t particl_number = gid % PARTICLE_COUNT;
	int color = 0x0000FF;
	float2 rand = (float2)(rand_x, rand_y);

	img[(int)pt[particl_number].pos.x + (int)pt[particl_number].pos.y * WIDTH] = 0x000000;
	pt[particl_number].pos += pt[particl_number].velocity * PARTICLE_SPEED;
	if (pt[particl_number].pos.x > WIDTH)
		pt[particl_number].velocity.x = -pt[particl_number].velocity.x;
	if (pt[particl_number].pos.x <= 0)
		pt[particl_number].velocity.x = -pt[particl_number].velocity.x;
	if (pt[particl_number].pos.y > HEIGHT)
		pt[particl_number].velocity.y = -pt[particl_number].velocity.y;
	if (pt[particl_number].pos.y < 0)
		pt[particl_number].velocity.y = -pt[particl_number].velocity.y;

	if (mouse->lkm == 1)
	{
		pt[particl_number].velocity.x = mouse->mouse_x - pt[particl_number].pos.x;
		pt[particl_number].velocity.y = mouse->mouse_y - pt[particl_number].pos.y;
		pt[particl_number].velocity = normalize(pt[particl_number].velocity);
//		pt[particl_number].velocity += rand;
		pt[particl_number].pos += pt[particl_number].velocity * PARTICLE_SPEED;
	}
	else if (mouse->lkm == 3 || mouse->lkm == 4)
	{
		pt[particl_number].velocity.x = pt[particl_number].pos.x - mouse->mouse_x;
		pt[particl_number].velocity.y = pt[particl_number].pos.y - mouse->mouse_y;
		pt[particl_number].velocity = normalize(pt[particl_number].velocity);
		pt[particl_number].pos += pt[particl_number].velocity * PARTICLE_SPEED;
	}

	if (pt[particl_number].pos.x > WIDTH)
		pt[particl_number].pos.x = WIDTH;
	if (pt[particl_number].pos.x <= 0)
		pt[particl_number].pos.x = 0;
	if (pt[particl_number].pos.y > HEIGHT)
		pt[particl_number].pos.y = HEIGHT;
	if (pt[particl_number].pos.y < 0)
		pt[particl_number].pos.y = 0;
	img[(int)pt[particl_number].pos.x + (int)pt[particl_number].pos.y * WIDTH] = color;
}