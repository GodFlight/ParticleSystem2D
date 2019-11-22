#include "particale_system.h"

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
	ret |= clReleaseMemObject(ps->gpu_mem->particle);
	ret |= clReleaseMemObject(ps->gpu_mem->img);
	ret |= clReleaseMemObject(ps->host_mem.mouse);
	if (ret == 0)
		return (1);
	else
		return (0);
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
	data->host_mem.mouse = clCreateBuffer(data->cl.context, CL_MEM_READ_ONLY | CL_MEM_USE_HOST_PTR,
										  sizeof(t_mouse_events), &data->events, &ret);
	ret = clSetKernelArg(data->cl.kernel, 0, sizeof(cl_mem), &data->gpu_mem->img);
	ret = clSetKernelArg(data->cl.kernel, 1, sizeof(cl_mem), &data->gpu_mem->particle);
	ret = clSetKernelArg(data->cl.kernel, 2, sizeof(cl_mem), &data->host_mem.mouse);
	ret = clEnqueueNDRangeKernel(data->cl.queue, data->cl.kernel, 1, NULL, &global_size, NULL, 0, NULL, NULL);
	ret = clEnqueueReadBuffer(data->cl.queue, data->gpu_mem->img, CL_TRUE, 0,
							  sizeof(int) * WIDTH * HEIGHT, data->sdl->data, 0, NULL, NULL);
}