#include "lemin.h"

static void			print_map(t_array *buffer)
{
	while (buffer)
	{
		if (!buffer->data)
			break;
		ft_putendl(buffer->data);
		buffer = buffer->next;
	}
	ft_putchar('\n');
}

int					main(int ac, char **av)
{
	t_array		*buffer;
	t_data		*data;

	(void)ac;
	(void)av;
	buffer = NULL;
	store_map(&buffer);
	data = (t_data*)ft_memalloc(sizeof(t_data));
	if (buffer && data && !init_data(data, buffer) && is_valid(data->graph))
	{
		print_map(buffer);
		start_resolver(data);
		// FIXME: Algorithm????
	}
	else
		ft_putstr("ERROR\n");
	destroy_array(buffer);
	return (0);
}
