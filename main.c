#include "particale_system.h"

void         ps_error_manager(const char *str, const int id)
{
    printf("%s ----> ERROR <---- %s\n", KRED, KNRM);
    printf("INCORRECT: %s%s%s%s%s\n",
           str,
           id < 0 ? "" : " IN ID = ",
           KGRN,
           id < 0 ? "" : ft_itoa(id),
           KNRM);
    exit(-1);
}

int	close_cl(t_ps_main *ps)
{
	int ret;

	ret = 0;
	ret |= clFinish(ps->cl.queue);
	ret |= clFlush(ps->cl.queue);
	ret |= clReleaseContext(ps->cl.context);
	ret |= clReleaseProgram(ps->cl.programs);
	ret |= clReleaseCommandQueue(ps->cl.queue);
	ret |= clReleaseDevice(ps->cl.device_id);
	ret |= clReleaseKernel(ps->cl.kernel);
	ret |= clReleaseMemObject(ps->cl.img);
	if (ret == 0)
		return (1);
	else
		return (0);
}

void	sdl_init(t_sdl **sdl)
{
	if (!(*sdl = (t_sdl *)ft_memalloc(sizeof(t_sdl))))
		ps_error_manager("COULD NOR ALLOCATED MEMORY IN SDL STRUCT", -1);
	if (!((*sdl)->data = (int *)ft_memalloc(sizeof(int) * WIDTH * HEIGHT)))
		ps_error_manager("COULD NOR ALLOCATED MEMORY IN SDL DATA", -1);
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_TIMER))
		ps_error_manager("COULD NOT INIT SDL", -1);
	(*sdl)->win_w = WIDTH;
	(*sdl)->win_h = HEIGHT;
	if(!((*sdl)->win = SDL_CreateWindow("PARTICALE SYSTEM", SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED, (*sdl)->win_w, (*sdl)->win_h, SDL_WINDOW_RESIZABLE)))
		ps_error_manager("COULD NOT CREATE SDL WIN", -1);
	(*sdl)->renderer = SDL_CreateRenderer((*sdl)->win, -1, 0);
	(*sdl)->texture = SDL_CreateTexture((*sdl)->renderer, SDL_PIXELFORMAT_BGRA32,
			SDL_TEXTUREACCESS_STATIC, (*sdl)->win_w, (*sdl)->win_h);
}

void		ps_main_init(t_ps_main *ps)
{
	if (!(ps = (t_ps_main *)ft_memalloc(sizeof(t_ps_main))))
		ps_error_manager("COULD NOT ALLOCATED MEMORY IN PS STRUCT", -1);
}

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

void 	fill_gpu_mem(t_ps_main *ps)
{
	int ret;

	if (!(ps->gpu_mem = (t_gpu_mem *)ft_memalloc((sizeof(t_gpu_mem)))))
		exit(-1);
	ps->gpu_mem->img = clCreateBuffer(ps->cl.context, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR,
									  sizeof(int) * WIDTH * HEIGHT, ps->sdl->data, &ret);
	ps->gpu_mem->particle = clCreateBuffer(ps->cl.context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
										   sizeof(t_particle) * PARTICLE_COUNT, ps->partcl, &ret);
}

char 	*read_kernels(char *path, size_t *len)
{
	int		i;
	int		fd;
	char	*buf;

	fd = open(path, O_RDONLY);
	if (!(buf = (char *)ft_memalloc(sizeof(buf) * 10000)))
		exit (-1);
	i = read(fd, buf, 10000);
	buf[i] = '\0';
	close(fd);
	*len = i;
	return (buf);
}

void	cl_init(t_ps_main *data)
{
	int			ret;
	char		*kernel;
	size_t		kernel_len;

	ret = 0;
	ret = clGetPlatformIDs(1, &data->cl.platform_id,
						   &ret);
	ret = clGetDeviceIDs(data->cl.platform_id, CL_DEVICE_TYPE_GPU,
						 1, &data->cl.device_id, &ret);
	data->cl.context = clCreateContext(NULL, 1, &data->cl.device_id,
									   NULL, NULL, &ret);
	data->cl.queue = clCreateCommandQueue(data->cl.context, data->cl.device_id,
										  0, &ret);
	kernel = read_kernels("../particle_kernel.cl", &kernel_len);
	data->cl.programs = clCreateProgramWithSource(data->cl.context, 1, (const char **)&kernel, &kernel_len, &ret);
	free(kernel);
	ret = clBuildProgram(data->cl.programs, 1, &data->cl.device_id, "-DOPENCL___ -I include/ ", NULL, NULL);
	data->cl.kernel = clCreateKernel(data->cl.programs, "particle", &ret);
	fill_gpu_mem(data);
}

void	run_cl(t_ps_main *data)
{
	int		ret;
	size_t	global_size;
	size_t 	local_size[2];

	ret = 0;
	local_size[0] = 256;
	local_size[1] = 1;
	global_size = PARTICLE_COUNT;
	ret = clSetKernelArg(data->cl.kernel, 0, sizeof(cl_mem), &data->gpu_mem->img);
	ret = clSetKernelArg(data->cl.kernel, 1, sizeof(cl_mem), &data->gpu_mem->particle);
	ret = clEnqueueNDRangeKernel(data->cl.queue, data->cl.kernel, 1, NULL, &global_size, NULL, 0, NULL, NULL);
	ret = clEnqueueReadBuffer(data->cl.queue, data->gpu_mem->img, CL_TRUE, 0,
			sizeof(int) * WIDTH * HEIGHT, data->sdl->data, 0, NULL, NULL);
}

void	main_loop(t_ps_main *ps, t_sdl *sdl)
{
	while (1337)
	{
		run_cl(ps);
		SDL_SetRenderTarget(sdl->renderer, sdl->texture);
		SDL_RenderClear(sdl->renderer);
		SDL_UpdateTexture(sdl->texture, NULL, (void *)sdl->data, sdl->win_w * sizeof(int));
		SDL_SetRenderTarget(sdl->renderer, NULL);
		SDL_RenderCopy(sdl->renderer, sdl->texture, NULL, NULL);
		SDL_RenderPresent(sdl->renderer);
		if (SDL_PollEvent(&sdl->event))
		{
			if ((sdl->event.type == SDL_QUIT) ||
				(sdl->event.type == SDL_KEYDOWN &&
				 sdl->event.key.keysym.scancode == SDL_SCANCODE_ESCAPE))
				break;
		}
	}
	close_cl(ps);
	SDL_DestroyRenderer(sdl->renderer);
	SDL_DestroyTexture(sdl->texture);
	SDL_Quit();
	exit(0);
}

int         main(void)
{
	t_ps_main ps;

	ps_main_init(&ps);
	sdl_init(&ps.sdl);
	particle_init(&ps.partcl);
	cl_init(&ps);
	main_loop(&ps, ps.sdl);
	return (0);
}