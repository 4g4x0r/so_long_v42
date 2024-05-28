#include "so_long.h"
int	handle_keys(t_in *fw, char key)
{
	int	coord_x;
	int	coord_y;
	coord_x = 0;
	coord_y = 0;
	if (key == 'a')
		coord_x = -1;
	else if (key == 's')
		coord_y = 1;
	else if (key == 'd')
		coord_x = 1;
	else if (key == 'w')
		coord_y = -1;
	return (check_move(fw, coord_x, coord_y));
}
int	check_move(t_in *fw, int coord_x, int coord_y)
{
	if (fw->map->mapstruct[fw->player->y + coord_y]
		[fw->player->x + coord_x] != '1')
	{
		if (fw->map->mapstruct[fw->player->y + coord_y]
			[fw->player->x + coord_x] == 'C')
			fw->map->coins_gained += 1;
		check_coins(fw);
		if ((fw->map->mapstruct[fw->player->y + coord_y]
				[fw->player->x + coord_x] == '0')
			|| (fw->map->mapstruct[fw->player->y + coord_y]
				[fw->player->x + coord_x] == 'C')
			|| ((fw->map->mapstruct[fw->player->y + coord_y]
					[fw->player->x + coord_x] == 'E')
				&& (fw->map->coins_gained == fw->map->coins)))
		{
			handle_move(fw, fw->player, coord_x, coord_y);
			fw->map->moves += 1;
			ft_printf(BLUE"\nNumber of movements "RED"%i\n", fw->map->moves);
			ft_printf(BLUE"Coins "RED"%i"GREEN, fw->map->coins_gained);
			ft_printf("/"RED"%i\n"DEFAULT, fw->map->coins);
			return (0);
		}
	}
	return (1);
}
int	check_e(t_in *fw)
{
	if (fw->player->y == fw->map->exit_y && fw->player->x == fw->map->exit_x)
	{
		ft_printf(GREEN"\n¡Nivel completado, gracias por jugar!\n"DEFAULT);
		mlx_destroy_image(fw->map->mlx, fw->map->floor_ptr);
		mlx_destroy_image(fw->map->mlx, fw->map->wall_ptr);
		mlx_destroy_image(fw->map->mlx, fw->player->ptr);
		mlx_destroy_image(fw->map->mlx, fw->map->coin_ptr);
		mlx_destroy_image(fw->map->mlx, fw->map->exit_ptr);
		mlx_destroy_window(fw->map->mlx, fw->map->mlx_win);
		exit(0);
	}
	return (0);
}
void	ft_set_variables(t_in *fw)
{
	fw->map->coins = 0;
	fw->map->exitp = 0;
	fw->map->startp = 0;
	fw->map->zeros = 0;
	fw->map->ones = 0;
}