/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guortun- <guortun-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 19:53:29 by guortun-          #+#    #+#             */
/*   Updated: 2023/12/12 01:35:19 by guortun-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	mlx_process(t_in *fw)
{
	fw->map->wall_ptr = mlx_xpm_file_to_image(fw->map->mlx, "sprites/wall.xpm",
			&fw->map->width, &fw->map->height);
	fw->map->floor_ptr = mlx_xpm_file_to_image(fw->map->mlx,
			"sprites/floor.xpm", &fw->map->width, &fw->map->height);
	fw->map->exit_ptr = mlx_xpm_file_to_image(fw->map->mlx, "sprites/exit.xpm",
			&fw->map->width, &fw->map->height);
	fw->map->coin_ptr = mlx_xpm_file_to_image(fw->map->mlx, "sprites/coin.xpm",
			&fw->map->width, &fw->map->height);
	fw->player->ptr = mlx_xpm_file_to_image(fw->map->mlx,
			"sprites/p_down_t.xpm", &fw->map->width, &fw->map->height);
	fw->map->moves = 0;
	fw->map->coins_gained = 0;
	handle_move(fw, fw->player, 0, 0);
	return (0);
}

void	set_image_ptr(t_in *fw, int y, int x, void **image_ptr)
{
	if (fw->map->mapstruct[y][x] == '1')
		*image_ptr = fw->map->wall_ptr;
	else if (fw->map->mapstruct[y][x] == '0')
		*image_ptr = fw->map->floor_ptr;
	else if (fw->map->mapstruct[y][x] == 'P')
		*image_ptr = fw->map->floor_ptr;
	else if (fw->map->mapstruct[y][x] == 'E')
	{
		*image_ptr = fw->map->exit_ptr;
		fw->map->exit_x = x;
		fw->map->exit_y = y;
	}
	else if (fw->map->mapstruct[y][x] == 'C')
		*image_ptr = fw->map->coin_ptr;
	else
		*image_ptr = fw->map->floor_ptr;
}

void	put_item_to_buffer(t_in *fw, int *buffer_data, int y, int x)
{
	int		*image_data;
	void	*image_ptr;
	int		row;
	int		col;

	set_image_ptr(fw, y, x, &image_ptr);
	if (image_ptr)
	{
		image_data = put_data(image_ptr);
		row = 0;
		while (row < BPP)
		{
			col = 0;
			while (col < BPP)
			{
				buffer_data[(y * BPP + row) * (fw->map->columns * BPP) + (
						x * BPP + col)] = image_data[row * BPP + col];
				col++;
			}
			row++;
		}
	}
}

int	key_hook(int keycode, t_in *fw)
{
	char	letter;

	if (keycode == 53)
		close_window_event(fw);
	letter = convert_keycode_to_letter(keycode);
	if (letter != '/')
		ft_printf(YELLOW"\nYou pressed the %c key!"DEFAULT, letter);
	if (keycode == 0)
		handle_keys(fw, 'a');
	else if (keycode == 1)
		handle_keys(fw, 's');
	else if (keycode == 2)
		handle_keys(fw, 'd');
	else if (keycode == 13)
		handle_keys(fw, 'w');
	else
	{
		ft_printf(RED"\nInvalid key!"DEFAULT);
		return (1);
	}
	return (0);
}

char	convert_keycode_to_letter(int keycode)
{
	if (keycode == 0)
		return ('A');
	else if (keycode == 1)
		return ('S');
	else if (keycode == 2)
		return ('D');
	else if (keycode == 13)
		return ('W');
	else
		return ('/');
}
