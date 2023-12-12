/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guortun- <guortun-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 18:56:56 by guortun-          #+#    #+#             */
/*   Updated: 2023/12/12 02:01:36 by guortun-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	error_msg(char *msg)
{
	perror(msg);
	exit(1);
}

int	*put_data(void *image_ptr)
{
	int		*image_data;
	int		bpp;
	int		endian;
	int		size_line;

	size_line = 0;
	image_data = (int *)mlx_get_data_addr(image_ptr, &bpp, &size_line, &endian);
	return (image_data);
}

int	main(int argc, char **argv)
{
	t_map	c;
	t_en	player;
	t_in	fw;

	fw.map = &c;
	fw.player = &player;
	fw.player->value = 'P';
	c.map_name = argv[1];
	check_argc(argc);
	check_file_extension(argv[1], ".ber");
	process_map_file(&fw);
	fw.map->mlx = mlx_init();
	fw.map->mlx_win = mlx_new_window(fw.map->mlx, fw.map->columns * BPP,
			fw.map->lines * BPP, "Pokemon Adventures");
	mlx_process(&fw);
	mlx_key_hook(c.mlx_win, key_hook, &fw);
	mlx_hook(fw.map->mlx_win, 17, 0, close_window_event, &fw);
	//mlx_expose_hook(fw.map->mlx_win, expose_window_event, &fw);
	mlx_loop_hook(c.mlx, loop_hook, &fw);
	mlx_loop(fw.map->mlx);
	return (0);
}
