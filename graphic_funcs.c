#include "so_long.h"

int	loop_hook(t_in *fw)
{
	put_imgs(fw);
	return (0);
}

void	check_coins(t_in *fw)
{
	if (fw->map->coins_gained >= fw->map->coins){
		fw->map->exit_ptr = mlx_xpm_file_to_image(fw->map->mlx,
		"sprites/exit_open.xpm", &fw->map->width, &fw->map->height);
		mlx_put_image_to_window(fw->map->mlx, fw->map->mlx_win, fw->map->exit_ptr,
		fw->map->exit_x * BPP, fw->map->exit_y * BPP);
	}
}

void	free_map_struct(t_in *fw)
{
	int i;
	
	i = 0;
	while (i <= fw->map->lines)
	{
		if (fw->map->mapstruct[i] != NULL)
		{
			free(fw->map->mapstruct[i]);
		}
		i++;
	}
	mlx_destroy_display(fw->map->mlx);
	exit(1);
}

void	process_buffer_data(t_in *fw, int *buffer_data)
{
	int y;
	int x;
	
	y = 0;
	x = 0;
	while (y < fw->map->lines)
	{
		put_item_to_buffer(fw, buffer_data, y, x);
		x++;
		if (x >= fw->map->columns)
		{
			x = 0;
			y++;
		}
	}
}

void	put_imgs(t_in *fw)
{
	void *buffer_image;
	int bpp;
	int size_line;
	int endian;
	int *buffer_data;
	
	buffer_image = mlx_new_image(fw->map->mlx, fw->map->columns * BPP,
	fw->map->lines * BPP);
	buffer_data = (int *)mlx_get_data_addr(buffer_image, &bpp, &size_line, &endian);
	process_buffer_data(fw, buffer_data);
	mlx_put_image_to_window(fw->map->mlx, fw->map->mlx_win, buffer_image, 0, 0);
	draw_image(fw, fw->player->ptr, fw->player->x * BPP, fw->player->y * BPP);
	mlx_do_sync(fw->map->mlx); //HE PROBADO A QUITAR ESTO Y EN EL PORTATIL TIENE MENOS BUG VISUAL DE CHIRIBITAS.
	mlx_destroy_image(fw->map->mlx, buffer_image);
}
