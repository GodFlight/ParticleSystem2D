
#include "../include/particale_system.h"

float lerp(float v0, float v1, float t)
{
	t = clamp(t, 0.f, 1.f);
	return (1.f - t) * v0 + t * v1;
}

int  get_color(float speed)
{
	int start = START_COLOR;
	int end = END_COLOR;
	int red = lerp((start >> 16) & 0xFF, (end >> 16) & 0xFF, speed);
	int green = lerp((start >> 8) & 0xFF, (end >> 8) & 0xFF, speed);
	int blue = lerp(start & 0xFF, end & 0xFF, speed);
	return ((red << 16) | (green << 8) | blue);
}

__kernel void particle(__global int *img, __global t_particle *pt,
			__global t_mouse_events *mouse)
{
	int gid = get_global_id(0);
	size_t particl_number = gid % PARTICLE_COUNT;
	float2 direction = (float2)(mouse->mouse_x, mouse->mouse_y);
	if (pt[particl_number].pos.x <= WIDTH && pt[particl_number].pos.x > 0
		&& pt[particl_number].pos.y > 0 && pt[particl_number].pos.y <= HEIGHT)
		img[(int)pt[particl_number].pos.x + (int)pt[particl_number].pos.y * WIDTH] = 0x000000;

	if (pt[particl_number].velocity.x != 0.f && pt[particl_number].velocity.y != 0.f)
		pt[particl_number].velocity *= SLOW_DOWN;
	pt[particl_number].pos += pt[particl_number].velocity * PARTICLE_SPEED;

//	if (pt[particl_number].pos.x > WIDTH)
//		pt[particl_number].velocity.x = -pt[particl_number].velocity.x;
//	if (pt[particl_number].pos.x <= 0)
//		pt[particl_number].velocity.x = -pt[particl_number].velocity.x;
//	if (pt[particl_number].pos.y > HEIGHT)
//		pt[particl_number].velocity.y = -pt[particl_number].velocity.y;
//	if (pt[particl_number].pos.y < 0)
//		pt[particl_number].velocity.y = -pt[particl_number].velocity.y;

	float2 view_direction = direction - pt[particl_number].pos;
	view_direction = normalize(view_direction);

	if (mouse->lkm == 1)
			pt[particl_number].velocity += view_direction + RANDOM_VELOCITY;
	else if (mouse->lkm == 3 || mouse->lkm == 4)
	{
		pt[particl_number].velocity = -view_direction + RANDOM_VELOCITY;
		pt[particl_number].pos += pt[particl_number].velocity * PARTICLE_SPEED * 10;
	}

	int color = get_color(length(pt[particl_number].velocity) * 0.01f);
//	if (pt[particl_number].pos.x > WIDTH)
//		pt[particl_number].pos.x = WIDTH;
//	if (pt[particl_number].pos.x <= 0)
//		pt[particl_number].pos.x = 0;
//	if (pt[particl_number].pos.y > HEIGHT)
//		pt[particl_number].pos.y = HEIGHT;
//	if (pt[particl_number].pos.y < 0)
//		pt[particl_number].pos.y = 0;
	if (pt[particl_number].pos.x <= WIDTH && pt[particl_number].pos.x > 0
		&& pt[particl_number].pos.y > 0 && pt[particl_number].pos.y <= HEIGHT)
	img[(int)pt[particl_number].pos.x + (int)pt[particl_number].pos.y * WIDTH] = color;
}