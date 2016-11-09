#include "lemin.h"

int					main(int ac, char **av)
{
	t_array		*buffer;
	t_data		*data;

	(void)ac;
	(void)av;
	buffer = NULL;
	store_map(&buffer);
	data = (t_data*)ft_memalloc(sizeof(t_data));
	if (buffer && data && !init_data(data, buffer))
	{
		// FIXME: Algorithm????
	}
	else
		ft_putstr("ERROR\n");
	destroy_array(buffer);
	return (0);
}
