#include "so_long.h"
int	get_pixel_color(void	*img_ptr, int	x, int	y)
{
    int	bpp;
    int	size_line;
    int	endian;
    char *img_data;

    img_data = mlx_get_data_addr(img_ptr, &bpp, &size_line, &endian);
    int	color = *(int	*)(img_data + y * size_line + x * (bpp / 8)); // color del pixel en (x,y)
    return color;
}

void	draw_image(in *fw, void	*img_ptr, int	start_x, int	start_y)
{
    int	x;
	int	y;
    int	color;
	int	width;
	int	height;
	int	exclude_color;
	width = BPP;
	height = BPP;
	exclude_color = get_pixel_color(img_ptr, 0, 0);
	//ft_printf("\nValor del pixel = %i\n", exclude_color); 		DEBUG
    y = 0;
    while (y < height)
    {
        x = 0;
        while (x < width)
        {
            color = get_pixel_color(img_ptr, x, y);
            if (color != exclude_color) // si el color no es el color excluido
            {
                mlx_pixel_put(fw->map->mlx, fw->map->mlx_win, start_x + x, start_y + y, color);
            }
            x++;
        }
        y++;
    }
}

int close_window_event(in *fw)
{
	printf("\nCerrando el juego...\n");
	mlx_destroy_display(fw->map->mlx);
    exit(0);  // Salir del programa
}

int expose_window_event(in *fw)
{
	if (fw)
	{
		printf("El tamaño de este juego no es modificable.\n");
	}
	return(0);
}