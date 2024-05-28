#include "so_long.h"
int	get_pixel_color(void *img_ptr, int x, int y)
{
	int		bpp;
	int		size_line;
	int		endian;
	char	*img_data;
	int		color;
	img_data = mlx_get_data_addr(img_ptr, &bpp, &size_line, &endian);
	color = *(int *)(img_data + y * size_line + x * (bpp / 8));
	return (color);
}
void	draw_image(t_in *fw, void *img_ptr, int start_x, int start_y)
{
	int	x;
	int	y;
	int	color;
	int	width;
	int	height;
	width = BPP;
	height = BPP;
	y = 0;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			color = get_pixel_color(img_ptr, x, y);
			if (color != 16650976)
			{
				mlx_pixel_put(fw->map->mlx, fw->map->mlx_win, start_x + x,
					start_y + y, color);
			}
			x++;
		}
		y++;
	}
}
int	close_window_event(t_in *fw)
{
	if (fw)
		printf(RED"\nClosing the game...\n"DEFAULT);
	exit(0);
}
int	expose_window_event(t_in *fw)
{
	static int	i;
	if (fw)
	{
		if (i != 0)
		{
			printf(RED"The size of this game is not modifiable.\n"DEFAULT);
			exit(1);
		}
		i++;
	}
	return (0);
}
int	draw_character(t_in *fw, t_en *en, int coordx, int coordy)
{
	en->ptr = mlx_xpm_file_to_image(fw->map->mlx,
			get_direction_static(en, coordx, coordy),
			&fw->map->width, &fw->map->height);
	return (0);
}