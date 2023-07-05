#include "so_long.h"

int	mlx_process(in *fw)
{
	fw->map->wall_ptr = mlx_xpm_file_to_image(fw->map->mlx, "sprites/wall.xpm", &fw->map->width, &fw->map->height);
	fw->map->floor_ptr = mlx_xpm_file_to_image(fw->map->mlx, "sprites/floor.xpm", &fw->map->width, &fw->map->height);
	fw->map->exit_ptr = mlx_xpm_file_to_image(fw->map->mlx, "sprites/exit.xpm", &fw->map->width, &fw->map->height);
	fw->map->coin_ptr = mlx_xpm_file_to_image(fw->map->mlx, "sprites/coin.xpm", &fw->map->width, &fw->map->height);
	fw->player->ptr = mlx_xpm_file_to_image(fw->map->mlx, "sprites/p_down_t.xpm", &fw->map->width, &fw->map->height);
	fw->map->moves = 0;
	fw->map->coins_gained = 0;
	//ft_printf("\n\nESTE ES EL VALOR DE WIDTH MOVE; %i\n", fw->count->widthmove);//	DEBUG
	handle_move(fw, fw->player, 0, 0);
	return (0);
}

void	set_image_ptr(in *fw, int y, int x, void **image_ptr)
{
    if (fw->map->mapstruct[y][x] == '1')
        *image_ptr = fw->map->wall_ptr;
    else if (fw->map->mapstruct[y][x] == '0')
        *image_ptr = fw->map->floor_ptr;
    else if (fw->map->mapstruct[y][x] == 'P') // When adding new enemies, put their letter here to indicate they are on the floor layer
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


void	put_item_to_buffer(in *fw, int *buffer_data, int y, int x)
{
    int *image_data;
    void *image_ptr;
    int bpp;
	int size_line;
	int endian;

	set_image_ptr(fw, y, x, &image_ptr);
    if (image_ptr)
    {
        image_data = (int *)mlx_get_data_addr(image_ptr, &bpp, &size_line, &endian);
		int row;
		row = 0;
		while (row < BPP)
		{
			int col;
			col = 0;
			while (col < BPP)
			{
				buffer_data[(y * BPP + row) * (fw->map->columns * BPP) + (x * BPP + col)] = image_data[row * BPP + col];
				col++;
			}
			row++;
		}
    }
}

int	key_hook(int keycode, in *fw)
{
	if (keycode == 65307)
	{
		ft_printf(YELLOW"\nYou pressed the "RED"ESC"DEFAULT" key...\n"MAGENTA"Closing the game.\n"DEFAULT);
		free_map_struct(fw);
	}
	char letter;
	letter = convert_keycode_to_letter(keycode);
	ft_printf(YELLOW"\nYou pressed the %c key!"DEFAULT, letter);
	if (keycode == 0x61 || keycode == 0x41 || keycode == 0) // Key 'a' or 'A' (the last one is for Mac!)
		handle_keys(fw, 'a');
	else if (keycode == 0x73 || keycode == 0x53 || keycode == 1) // Key 's' or 'S'
		handle_keys(fw, 's');
	else if (keycode == 0x64 || keycode == 0x44 || keycode == 2) // Key 'd' or 'D'
		handle_keys(fw, 'd');
	else if (keycode == 0x77 || keycode == 0x57 || keycode == 13) // Key 'w' or 'W'
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
	if (keycode >= 65 && keycode <= 90)
		return (char)keycode;  // ASCII codes for uppercase letters
	else if (keycode >= 97 && keycode <= 122)
		return (char)(keycode - 32);  // ASCII codes for lowercase letters, converted to uppercase
	else
		return '\0';  // Null value to indicate an error
}


int	is_entity(in *fw, int y, int x, int first_time)
{
	if (fw->map->mapstruct[y][x] == 'P' && first_time == 2)
	{
		mlx_put_image_to_window(fw->map->mlx, fw->map->mlx_win, fw->map->floor_ptr, x * BPP, y * BPP);
		draw_image(fw, fw->player->ptr, fw->player->x * BPP, fw->player->y * BPP);
		return 1;
	}
	return 0;
}
