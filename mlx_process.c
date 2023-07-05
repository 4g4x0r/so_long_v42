#include "so_long.h"

int mlx_process(in *fw)
{
	fw->map->wall_ptr = mlx_xpm_file_to_image(fw->map->mlx, "sprites/wall.xpm", &fw->map->width, &fw->map->height);
	fw->map->floor_ptr = mlx_xpm_file_to_image(fw->map->mlx, "sprites/floor.xpm", &fw->map->width, &fw->map->height);
	fw->map->exit_ptr = mlx_xpm_file_to_image(fw->map->mlx, "sprites/exit.xpm", &fw->map->width, &fw->map->height);
	fw->map->coin_ptr = mlx_xpm_file_to_image(fw->map->mlx, "sprites/coin.xpm", &fw->map->width, &fw->map->height);
	fw->player->ptr = mlx_xpm_file_to_image(fw->map->mlx, "sprites/p_down_t.xpm", &fw->map->width, &fw->map->height);
	fw->map->moves = 0;
	fw->map->coins_gained = 0;
	//ft_printf("\n\nESTE ES EL VALOR DE WIDTH MOVE; %i\n", fw->count->widthmove);//	DEBUG
	handlemove(fw, fw->player, 0, 0);
	return (0);
}

void put_item_to_buffer(in *fw, int *buffer_data, int y, int x)
{
    int *image_data;
    void *image_ptr = NULL;
    int bpp, size_line, endian;

	if (fw->map->mapstruct[y][x] == '1')
	 	image_ptr = fw->map->wall_ptr;
	else if (fw->map->mapstruct[y][x] == '0')
		image_ptr = fw->map->floor_ptr;
	else if (fw->map->mapstruct[y][x] == 'P')//al agregar nuevos enemigos, poner su letra aqui para saber que estan en la capa del suelo
		image_ptr = fw->map->floor_ptr;
	else if (fw->map->mapstruct[y][x] == 'E')
	{
		image_ptr = fw->map->exit_ptr;
		fw->map->exit_x = x;
		fw->map->exit_y = y;
	}
	else if (fw->map->mapstruct[y][x] == 'C')
		image_ptr = fw->map->coin_ptr;
	else 
		image_ptr = fw->map->floor_ptr;
    if (image_ptr)
    {
        image_data = (int *)mlx_get_data_addr(image_ptr, &bpp, &size_line, &endian);
        int cell_width = size_line / (bpp / 8);
        int cell_height = BPP;

        for (int row = 0; row < cell_height; row++) {
            for (int col = 0; col < cell_width; col++) {
                int buffer_x = x * cell_width + col;
                int buffer_y = y * cell_height + row;
                int image_index = row * cell_width + col;
                int buffer_index = buffer_y * (fw->map->columns * cell_width) + buffer_x;
                buffer_data[buffer_index] = image_data[image_index];
            }
        }
    }
}
int key_hook(int keycode, in *fw)
{
	if (keycode == 65307)
	{
		ft_printf(YELLOW"\nHas pulsado la tecla "RED"ESC"DEFAULT" ...\n"MAGENTA"Cerrando el juego.\n"DEFAULT);
		free_mapstruct(fw);
	}
	char letra = convertirKeyCodeALetra(keycode);
	ft_printf(YELLOW"\nHas pulsado la tecla %c!"DEFAULT, letra);
	if (keycode == 0x61 || keycode == 0x41 || keycode == 0) // tecla a o A ¡EL ULTIMO ES PARA MAC!.
		handlekeys(fw, 'a');
	else if (keycode == 0x73 || keycode == 0x53 || keycode == 1) // tecla s o S
		handlekeys(fw, 's');
	else if (keycode == 0x64 || keycode == 0x44 || keycode == 2) // tecla d o D
		handlekeys(fw, 'd');
	else if (keycode == 0x77 || keycode == 0x57 || keycode == 13) // tecla w o W
		handlekeys(fw, 'w');
	else
	{
		ft_printf(RED"\n¡Tecla inválida!"DEFAULT);
		return (1);
	}
	return (0);
}

char convertirKeyCodeALetra(int keycode) {
	
	if (keycode >= 65 && keycode <= 90)
        return (char)keycode;  // Códigos ASCII para letras mayúsculas
    else if (keycode >= 97 && keycode <= 122)
	{
        keycode -= 32;
		return ((char)keycode);  // Códigos ASCII para letras minúsculas
    }
	else
        return ('\0');  // Valor nulo para indicar un error
}
int is_entity(in *fw, int y, int x, int first_time)
{
	if (fw->map->mapstruct[y][x] == 'P' && first_time == 2)
	{
		mlx_put_image_to_window(fw->map->mlx, fw->map->mlx_win, fw->map->floor_ptr, x * BPP, y * BPP);
		draw_image(fw, fw->player->ptr, fw->player->x * BPP, fw->player->y * BPP);
		return(1);
	}
	return(0);
}