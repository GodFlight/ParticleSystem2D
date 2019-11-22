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


void	update_window(t_ps_main *ps, t_sdl *sdl)
{
	SDL_RenderClear(sdl->renderer);
	SDL_SetRenderTarget(sdl->renderer, sdl->texture);
	SDL_UpdateTexture(sdl->texture, NULL, (void *)sdl->data, sdl->win_w * sizeof(int));
	SDL_SetRenderTarget(sdl->renderer, NULL);
	SDL_RenderCopy(sdl->renderer, sdl->texture, NULL, NULL);
	SDL_RenderPresent(sdl->renderer);
}

void	check_event(t_ps_main *ps, t_sdl *sdl)
{

	if (sdl->event.type == SDL_MOUSEBUTTONDOWN && (sdl->event.button.button == SDL_BUTTON_LEFT
												   || sdl->event.button.button == SDL_BUTTON_RIGHT))
	{
		ps->events.mouse_x = sdl->event.button.x;
		ps->events.mouse_y = sdl->event.button.y;
		ps->events.lkm = sdl->event.button.button;
	}
	else if (sdl->event.type == SDL_MOUSEMOTION && (sdl->event.motion.state == SDL_BUTTON_LMASK
													|| sdl->event.motion.state == SDL_BUTTON_RMASK))
	{
		ps->events.mouse_x = sdl->event.button.x;
		ps->events.mouse_y = sdl->event.button.y;
		ps->events.lkm = sdl->event.motion.state;
	}
	else
		ps->events.lkm = 0;
}

void	main_loop(t_ps_main *ps, t_sdl *sdl)
{
	while (1337)
	{
		update_window(ps, sdl);
		run_cl(ps);
		if (SDL_PollEvent(&sdl->event))
		{
			if ((sdl->event.type == SDL_QUIT) ||
				(sdl->event.type == SDL_KEYDOWN &&
				 sdl->event.key.keysym.scancode == SDL_SCANCODE_ESCAPE))
				break;
			check_event(ps, sdl);
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