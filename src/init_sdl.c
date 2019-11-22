#include "particale_system.h"

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