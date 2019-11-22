#include "particale_system.h"

void		event_init(t_ps_main *ps)
{
	ps->events.lkm = 0;
	ps->events.mouse_x = WIDTH / 2;
	ps->events.mouse_y = HEIGHT / 2;
}

void		ps_main_init(t_ps_main *ps)
{
	if (!(ps = (t_ps_main *)ft_memalloc(sizeof(t_ps_main))))
		ps_error_manager("COULD NOT ALLOCATED MEMORY IN PS STRUCT", -1);
	event_init(ps);
}
