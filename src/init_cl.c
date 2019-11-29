#include "particale_system.h"

void 	fill_gpu_mem(t_ps_main *ps)
{
	int ret;

	if (!(ps->gpu_mem = (t_gpu_mem *)ft_memalloc((sizeof(t_gpu_mem)))))
		exit(-1);
	ps->gpu_mem->img = clCreateBuffer(ps->cl.context, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR,
									  sizeof(int) * WIDTH * HEIGHT, ps->sdl->data, &ret);
	ps->gpu_mem->particle = clCreateBuffer(ps->cl.context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
										   sizeof(t_particle) * PARTICLE_COUNT, ps->partcl, &ret);
	free(ps->partcl);
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
	kernel = read_kernels("./src/particle_kernel.cl", &kernel_len);
	data->cl.programs = clCreateProgramWithSource(data->cl.context, 1, (const char **)&kernel, &kernel_len, &ret);
	free(kernel);
	ret = clBuildProgram(data->cl.programs, 1, &data->cl.device_id, "-DOPENCL___ -I include/ ", NULL, NULL);
	data->cl.kernel = clCreateKernel(data->cl.programs, "particle", &ret);
	fill_gpu_mem(data);
}