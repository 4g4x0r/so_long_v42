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

char* put_values(char *cadena, entity *entity) {
    char *copia = ft_strdup(cadena);  // Crear una copia de la cadena original
    copia[8] = get_low(entity->value);
    return copia;
}

char get_low(char letter)
{
    if (letter >= 'A' && letter <= 'Z') {
        return letter + 32;
    } else {
        // Si la letra no es mayúscula, se devuelve tal cual
        return letter;
    }
}
char *getdirectionstatic(entity *entity, int	coordx, int	coordy){
	char *imgstep;
	imgstep = put_values("sprites/p_down_t.xpm", entity);//default
	if (coordx == -1) //a
		imgstep = put_values("sprites/p_left_t.xpm", entity);
	else if (coordy == 1) //s
		imgstep = put_values("sprites/p_down_t.xpm", entity);
	else if (coordx == 1) //d
		imgstep = put_values("sprites/p_right_t.xpm", entity);
	else if (coordy == -1) //w
		imgstep = put_values("sprites/p_up_t.xpm", entity);
	return imgstep;
}

int	drawcharacter(in *fw, entity *entity, int	coordx, int	coordy) {
	entity->stepanimation++;
	if (entity->stepanimation == 2)
		entity->ptr = mlx_xpm_file_to_image(fw->map->mlx, getdirectionstatic(entity, coordx, coordy), &fw->map->width, &fw->map->height);
	else if (entity->stepanimation == 4)
	{
		entity->ptr = mlx_xpm_file_to_image(fw->map->mlx, getdirectionstatic(entity, coordx, coordy), &fw->map->width, &fw->map->height);
		entity->stepanimation = 0;
	}
	return (entity->stepanimation);
}
void	initplayer(in *fw, entity *entity, int	coordx, int	coordy) {
	fw->map->mapstruct[entity->y][entity->x] = '0';
	if (fw->map->mapstruct[entity->y + coordy][entity->x + coordx] != 'E')
		fw->map->mapstruct[entity->y + coordy][entity->x + coordx] = entity->value;
}
void handlemove(in *fw, entity *entity, int coordx, int coordy){
	initplayer(fw, entity, coordx, coordy);

	entity->x += coordx;
	entity->y += coordy;
	entity->ptr = mlx_xpm_file_to_image(fw->map->mlx, getdirectionstatic(entity, coordx, coordy), &fw->map->width, &fw->map->height);//CARGA LA DIRECCION ESTATICA DEL JUGADOR.
	mlx_do_sync(fw->map->mlx);
	check_e(fw);
}
