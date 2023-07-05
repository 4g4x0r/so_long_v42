#include "so_long.h"

int	loop_hook(in *fw)
{
	put_imgs(fw);
    return (0);
}

void	check_coins(in *fw)
{
	if (fw->map->coins_gained >= fw->map->coins){
		fw->map->exit_ptr = mlx_xpm_file_to_image(fw->map->mlx, "sprites/exit_open.xpm", &fw->map->width, &fw->map->height);
		mlx_put_image_to_window(fw->map->mlx, fw->map->mlx_win, fw->map->exit_ptr, fw->map->exit_x * BPP, fw->map->exit_y * BPP);
	}
}

int	draw_character(in *fw, entity *entity, int	coordx, int	coordy) {
	entity->stepanimation++;
	if (entity->stepanimation == 2)
		entity->ptr = mlx_xpm_file_to_image(fw->map->mlx, get_direction_static(entity, coordx, coordy), &fw->map->width, &fw->map->height);
	else if (entity->stepanimation == 4)
	{
		entity->ptr = mlx_xpm_file_to_image(fw->map->mlx, get_direction_static(entity, coordx, coordy), &fw->map->width, &fw->map->height);
		entity->stepanimation = 0;
	}
	return (entity->stepanimation);
}

void free_map_struct(in *fw)
{
	int i = 0;
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

void put_imgs(in *fw)
{
	int y, x;
    void *buffer_image = mlx_new_image(fw->map->mlx, fw->map->columns * BPP, fw->map->lines * BPP);
	int bpp, size_line, endian;
    int *buffer_data = (int *)mlx_get_data_addr(buffer_image, &bpp, &size_line, &endian);
	y = 0;
	x = 0;
	while (y < fw->map->lines)
	{
		put_item_to_buffer(fw, buffer_data, y, x);
		x++;
		if (x >= fw->map->columns) {
			x = 0;
			y++;
		}
	}
    mlx_put_image_to_window(fw->map->mlx, fw->map->mlx_win, buffer_image, 0, 0);
	draw_image(fw, fw->player->ptr, fw->player->x * BPP, fw->player->y * BPP);
	mlx_do_sync(fw->map->mlx);//HE PROBADO A QUITAR ESTO Y EN EL PORTATIL TIENE MENOS BUG VISUAL DE CHIRIBITAS.
    mlx_destroy_image(fw->map->mlx, buffer_image);
}