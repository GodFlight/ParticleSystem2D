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
#define PARTICLE_COUNT 1000000

#ifndef OPENCL___
typedef struct		s_sdl
{
    SDL_Window		*win;
    SDL_Renderer	*renderer;
    SDL_Event		event;
    SDL_Texture		*texture;
    int 			*data;
    int 			x;
    int 			y;
    int				win_h;
    int				win_w;
    char 			*win_title;
}					t_sdl;

typedef struct 		s_gpu_mem
{
	cl_mem 			img;
	cl_mem 			particle;
}					t_gpu_mem;

typedef struct 		s_cl
{
	cl_command_queue	queue;
	cl_context			context;
	cl_program			programs;
	cl_device_id		device_id;
	cl_platform_id 		platform_id;
	cl_kernel 			kernel;
	cl_mem 				img;
}					t_cl;
#endif

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
typedef struct s_ps_main
{
	t_sdl       *sdl;
    t_cl		cl;
    t_gpu_mem	*gpu_mem;
    t_particle	*partcl;
}               t_ps_main;
#endif
#endif