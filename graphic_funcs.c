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