/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_moves.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guortun- <guortun-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 08:58:41 by guortun-          #+#    #+#             */
/*   Updated: 2023/10/04 20:07:17 by guortun-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	*put_values(char *string, t_en *en)
{
	char	*copy;

	copy = ft_strdup(string);
	copy[8] = get_low(en->value);
	return (copy);
}

char	get_low(char letter)
{
	if (letter >= 'A' && letter <= 'Z')
	{
		return (letter + 32);
	}
	else
		return (letter);
}

char	*get_direction_static(t_en *en, int coordx, int coordy)
{
	char	*imgstep;

	imgstep = put_values("sprites/p_down_t.xpm", en);
	if (coordx == -1)
	{
		imgstep = put_values("sprites/p_left_t.xpm", en);
	}
	else if (coordy == 1)
	{
		imgstep = put_values("sprites/p_down_t.xpm", en);
	}
	else if (coordx == 1)
	{
		imgstep = put_values("sprites/p_right_t.xpm", en);
	}
	else if (coordy == -1)
	{
		imgstep = put_values("sprites/p_up_t.xpm", en);
	}
	return (imgstep);
}

void	init_player(t_in *fw, t_en *en, int coordx, int coordy)
{
	fw->map->mapstruct[en->y][en->x] = '0';
	if (fw->map->mapstruct[en->y + coordy][en->x + coordx] != 'E')
		fw->map->mapstruct[en->y + coordy][en->x + coordx] = en->value;
}

void	handle_move(t_in *fw, t_en *en, int coordx, int coordy)
{
	init_player(fw, en, coordx, coordy);
	en->x += coordx;
	en->y += coordy;
	en->ptr = mlx_xpm_file_to_image(fw->map->mlx,
			get_direction_static(en, coordx, coordy),
			&fw->map->width, &fw->map->height);
	mlx_do_sync(fw->map->mlx);
	check_e(fw);
}
