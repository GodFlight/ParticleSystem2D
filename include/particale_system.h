#ifndef PARTICLE_SYSTEM_H
#define PARTICLE_SYSTEM_H

#ifndef OPENCL___
#include "libft.h"
#include <math.h>
#include <OpenCL/opencl.h>
#include "SDL.h"
#include "SDL_image.h"
#include "define.h"

#endif

#define WIDTH 1920
#define HEIGHT 1080
#define PARTICLE_COUNT 500000
#define RANDOM_VELOCITY 0.02f
#define PARTICLE_SPEED 0.1f
#define SLOW_DOWN 0.999f
#define START_COLOR 0x0000FF
#define END_COLOR 0xFF0000

#ifndef OPENCL___
typedef struct		s_sdl
{
    SDL_Window		*win;
    SDL_Renderer	*renderer;
    SDL_Event		event;
    SDL_Texture		*texture;
    int 			*data;
    int				win_h;
    int				win_w;
}					t_sdl;

typedef struct 		s_gpu_mem
{
	cl_mem 			img;
	cl_mem 			particle;
}					t_gpu_mem;

typedef struct 		s_host_mem
{
	cl_mem 			mouse;
}					t_host_mem;

typedef struct 		s_cl
{
	cl_command_queue	queue;
	cl_context			context;
	cl_program			programs;
	cl_device_id		device_id;
	cl_platform_id 		platform_id;
	cl_kernel 			kernel;
}					t_cl;
#endif

typedef struct		s_mouse_events
{
#ifndef OPENCL___
	cl_int 			mouse_x;
	cl_int 			mouse_y;
	char			lkm;
#else
	int				mouse_x;
	int				mouse_y;
	char			lkm;
#endif
}					t_mouse_events;

typedef struct 		s_particle
{
#ifndef OPENCL___
	cl_float2 		pos;
	cl_float2		velocity;
#else
	float2			pos;
	float2			velocity;
#endif
}					t_particle;

#ifndef OPENCL___
typedef struct		s_ps_main
{
	t_sdl			*sdl;
    t_cl			cl;
    t_gpu_mem		*gpu_mem;
    t_host_mem		host_mem;
    t_particle		*partcl;
    t_mouse_events	events;
}					t_ps_main;

void		ps_error_manager(const char *str, const int id);
void		cl_init(t_ps_main *data);
void		sdl_init(t_sdl **sdl);
void		particle_init(t_particle **partcl);
void		ps_main_init(t_ps_main *ps);
void		event_init(t_ps_main *ps);
void		run_cl(t_ps_main *data);
int			close_cl(t_ps_main *ps);

#endif
#endif

